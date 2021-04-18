#include "Lambertian.h"

bool Lambertian::scatter(const Ray& r, const hit_record& rec, Vector3D& attenuation, Ray& scattered) const
{
	Vector3D scatter_direction = rec.normal + random_unit_vector();

	//if rec.normal and random_unit_vector is the opposite direction
	if (scatter_direction.near_zero())
		scatter_direction = rec.normal;

	scattered = Ray(rec.pos, scatter_direction, r.time);
	attenuation = albedo;
	return true;
}