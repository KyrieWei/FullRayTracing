#include "YZ_Rect.h"

bool YZ_Rect::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	auto t = (k - r.origin.x) / r.direction.x;
	if (t < t_min || t < t_max)
		return false;

	auto y = r.origin.y + t * r.direction.y;
	auto z = r.origin.z + t * r.direction.z;

	if (y < y0 || y > y1 || z < z0 || z > z1)
		return false;

	rec.u = (y - y0) / (y1 - y0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	auto outward_normal = Vector3D(1, 0, 0);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mp;
	rec.pos = r.pointAt(t);

	return true;
}