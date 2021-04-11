#include "Lambertian.h"

bool Lambertian::scatter(const Ray& r, const hit_record& rec, Vector3D& attenuation, Ray& scattered) const
{
	Vector3D scatter_direction = rec.normal + random_in_unit_sphere();



	return true;
}