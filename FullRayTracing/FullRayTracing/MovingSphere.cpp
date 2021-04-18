#include "MovingSphere.h"

Vector3D MovingSphere::center(float time) const
{
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool MovingSphere::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	Vector3D oc = r.origin - center(r.time);
	float a = length_squared(r.direction);
	float half_b = dot(oc, r.direction);
	float c = length_squared(oc) - radius * radius;

	float discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	float sqrtd = sqrt(discriminant);

	float root = (-half_b - sqrtd) / a;
	if (root < t_min || root > t_max)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.pos = r.pointAt(rec.t);
	Vector3D outward_normal = (rec.pos - center(r.time)) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;

	return true;

}

bool MovingSphere::bounding_box(float time0, float time1, AABB& output_box) const
{
	AABB box0(center(time0) - Vector3D(radius, radius, radius), center(time0) + Vector3D(radius, radius, radius));
	AABB box1(center(time1) - Vector3D(radius, radius, radius), center(time1) + Vector3D(radius, radius, radius));

	output_box = surrounding_box(box0, box1);
	return true;
}