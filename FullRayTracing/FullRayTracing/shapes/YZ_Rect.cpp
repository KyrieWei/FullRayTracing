#include "YZ_Rect.h"

bool YZ_Rect::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	//光线从原点到达平面所需时间
	auto t = (k - r.origin.x) / r.direction.x;
	if (t < t_min || t > t_max)
		return false;

	//光线经过时间t后到达Y、Z维度的值
	auto y = r.origin.y + t * r.direction.y;
	auto z = r.origin.z + t * r.direction.z;

	if (y < y0 || y > y1 || z < z0 || z > z1)
		return false;

	rec.u = (y - y0) / (y1 - y0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;

	//法线指向X轴正方向
	auto outward_normal = Vector3D(1, 0, 0);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mp;
	rec.pos = r.pointAt(t);

	return true;
}