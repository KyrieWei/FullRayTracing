#include "Lambertian.h"
#include "../core/ONB.h"

bool Lambertian::scatter(const Ray& r, const hit_record& rec, Vector3D& alb, Ray& scattered) const
{
	Vector3D direction = rec.normal + random_unit_vector();

	scattered = Ray(rec.pos, unit_vector(direction), r.time);
	alb = albedo->value(rec.u, rec.v, rec.pos);
	//
	return true;

	//auto scatter_direction = rec.normal + random_unit_vector();

	//// Catch degenerate scatter direction
	//if (scatter_direction.near_zero())
	//	scatter_direction = rec.normal;

	//scattered = Ray(rec.pos, scatter_direction, r.time);
	//alb = albedo->value(rec.u, rec.v, rec.pos);
	//return true;
}

float Lambertian::scattering_pdf(const Ray& r, const hit_record& rec, const Ray& scattered) const
{
	auto cosine = dot(rec.normal, unit_vector(scattered.direction));
	return cosine < 0 ? 0 : cosine / M_PI;
}