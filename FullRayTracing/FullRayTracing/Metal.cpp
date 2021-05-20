#include "Metal.h"

bool Metal::scatter(const Ray& r, const hit_record& rec, Vector3D& attenuation, Ray& scattered, float& pdf) const
{
	Vector3D reflected_direction = reflect(unit_vector(r.direction), rec.normal);
	scattered = Ray(rec.pos, reflected_direction + fuzz * random_in_unit_sphere(), r.time);
	attenuation = albedo;
	return (dot(scattered.direction, rec.normal) > 0);
}