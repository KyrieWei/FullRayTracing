#include "XY_Rect.h"

bool XY_Rect::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	auto t = (k - r.origin.z) / r.direction.z;

	if (t < t_min || t > t_max)
		return false;

	auto x = r.origin.x + t * r.direction.x;
	auto y = r.origin.y + t * r.direction.y;
	if (x < x0 || x > x1 || y < y0 || y > y1)
		return false;

	rec.u = (x - x0) / (x1 - x0);
	rec.v = (y - y0) / (y1 - y0);
	rec.t = t;

	auto outward_normal = Vector3D(0, 0, 1);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mp;
	rec.pos = r.pointAt(t);
	return true;
}