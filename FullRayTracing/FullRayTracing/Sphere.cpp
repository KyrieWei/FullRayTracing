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
	get_sphere_uv(outward_normal, rec.u, rec.v);
	rec.mat_ptr = mat_ptr;

	return true;

}

bool Sphere::bounding_box(float time0, float time1, AABB& output_box) const
{
	output_box = AABB(center - Vector3D(radius, radius, radius), center + Vector3D(radius, radius, radius));
	return true;
}

void Sphere::get_sphere_uv(const Vector3D& p, float& u, float& v)
{
	//p : a given point on the sphere of radius one, centered at the origin
	//u : returned value [0,1] of angle around the Y axis from X = -1
	//v : returned value [0,1] of angle from Y = -1 to Y = +1
	//	<1, 0, 0> yields <0.50, 0.50>	  <-1, 0, 0> yields <0.00, 0.50>
	//	<0 1 0> yields <0.50, 1.00>       < 0 -1  0> yields <0.50, 0.00>
	//	<0 0 1> yields <0.25, 0.50>       < 0  0 -1> yields <0.75, 0.50>

	auto theta = acos(-p.y);
	auto phi = atan2(-p.z, p.x) + M_PI;

	u = phi / (2 * M_PI);
	v = theta / M_PI;
}
