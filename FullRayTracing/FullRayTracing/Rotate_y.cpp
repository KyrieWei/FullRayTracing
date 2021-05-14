#include "Rotate_y.h"

Rotate_y::Rotate_y(shared_ptr<Object> p, float angle) : ptr(p)
{
	auto radians = degrees_to_radians(angle);
	sin_theta = sin(radians);
	cos_theta = cos(radians);
	hasbox = ptr->bounding_box(0, 1, bbox);

	Vector3D min(INFINITY, INFINITY, INFINITY);
	Vector3D max(-INFINITY, -INFINITY, -INFINITY);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j ++)
			for (int k = 0; k < 2; k++)
			{
				auto x = i * bbox.maximum.x + (1 - i) * bbox.minimum.x;
				auto y = j * bbox.maximum.y + (1 - j) * bbox.minimum.y;
				auto z = k * bbox.maximum.z + (1 - k) * bbox.minimum.z;

				auto newx = cos_theta * x + sin_theta * z;
				auto newz = -sin_theta * x + cos_theta * z;

				Vector3D tester(newx, y, newz);

				for (int c = 0; c < 3; c++) 
				{
					min[c] = fmin(min[c], tester[c]);
					max[c] = fmax(max[c], tester[c]);
				}
			}

	bbox = AABB(min, max);
}

bool Rotate_y::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	auto origin = r.origin;
	auto direction = r.direction;

	origin[0] = cos_theta * r.origin.x - sin_theta * r.origin.z;
	origin[2] = sin_theta * r.origin.x + cos_theta * r.origin.z;

	direction[0] = cos_theta * r.direction.x - sin_theta * r.direction.z;
	direction[2] = sin_theta * r.direction.x - cos_theta * r.direction.z;

	Ray rotated_r(origin, direction, r.time);

	if (!ptr->hit(rotated_r, rec, t_min, t_max))
		return false;

	auto p = rec.pos;
	auto normal = rec.normal;

	p[0] = cos_theta * rec.pos[0] + sin_theta * rec.pos[2];
	p[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

	rec.pos = p;
	rec.set_face_normal(rotated_r, normal);

	return true;
}
