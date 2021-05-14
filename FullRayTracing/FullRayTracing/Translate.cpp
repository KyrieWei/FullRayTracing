#include "Translate.h"

bool Translate::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	Ray moved_r(r.origin - offset, r.direction, r.time);
	if (!ptr->hit(moved_r, rec, t_min, t_max))
		return false;

	rec.pos += offset;
	rec.set_face_normal(moved_r, rec.normal);

	return true;
}

bool Translate::bounding_box(float time0, float time1, AABB& output_box) const
{
	if (!ptr->bounding_box(time0, time1, output_box))
		return false;

	output_box = AABB(output_box.minimum + offset, output_box.maximum + offset);

	return true;

}