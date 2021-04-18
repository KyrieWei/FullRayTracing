#include "Sphere.h"


//sphere: (p - c)^2 = r^2   --   p is the point on the sphere, c is the center, r is the radius
//line :  p = o + t*d  --  p is the point on the line, o is the origin, d is the direction, t is param
//interact: (o + t*d - c)^2 = r^2  -- caculate t
//  a = d^2,  b = 2 * oc * d,  c = oc^2 - r^2
//  disc = b^2 / 4 - ac < 0 no root, 
//	t = (-b +/- sqrt(b^2 - 4ac)) / 2a
bool Sphere::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	Vector3D oc = r.origin - center;

	float a = length_squared(r.direction);
	float half_b = dot(oc, r.direction);
	float c = length_squared(oc) - radius * radius;

	float discriminant = half_b * half_b - a * c;

	//has no root
	if (discriminant < 0)
		return false;

	float sqrtd = sqrt(discriminant);
	float root = (-half_b - sqrtd) / a;
	if (root < t_min || root > t_max)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || root > t_max)
			return false;
	}

	rec.t = root;
	rec.pos = r.pointAt(root);
	Vector3D outward_normal = (rec.pos - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;

	return true;

}

bool Sphere::bounding_box(float time0, float time1, AABB& output_box) const
{
	output_box = AABB(center - Vector3D(radius, radius, radius), center + Vector3D(radius, radius, radius));
	return true;
}
