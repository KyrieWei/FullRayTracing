#include "AABB.h"


bool AABB::hit(const Ray& r, float t_min, float t_max) const
{
	//x
	float t_x0 = fmin((minimum.x - r.origin.x) / r.direction.x, (maximum.x - r.origin.x) / r.direction.x);
	float t_x1 = fmax((minimum.x - r.origin.x) / r.direction.x, (maximum.x - r.origin.x) / r.direction.x);

	//if overlap
	t_min = fmax(t_x0, t_min);
	t_max = fmin(t_x1, t_max);
	if (t_max <= t_min)
		return false;

	//y
	float t_y0 = fmin((minimum.y - r.origin.y) / r.direction.y, (maximum.y - r.origin.y) / r.direction.y);
	float t_y1 = fmax((minimum.y - r.origin.y) / r.direction.y, (maximum.y - r.origin.y) / r.direction.y);

	t_min = fmax(t_y0, t_min);
	t_max = fmin(t_y1, t_max);
	if (t_max <= t_min)
		return false;

	//z
	float t_z0 = fmin((minimum.z - r.origin.z) / r.direction.z, (maximum.z - r.origin.z) / r.direction.z);
	float t_z1 = fmax((minimum.z - r.origin.z) / r.direction.z, (maximum.z - r.origin.z) / r.direction.z);

	t_min = fmax(t_z0, t_min);
	t_max = fmin(t_z1, t_max);
	if (t_max <= t_min)
		return false;

	return true;
}