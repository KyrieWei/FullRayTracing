#include "Lambertian.h"
#include "ONB.h"

bool Lambertian::scatter(const Ray& r, const hit_record& rec, Vector3D& alb, Ray& scattered, float& pdf) const
{
	ONB uvw;
	uvw.build_from_w(rec.normal);
	auto direction = uvw.local(random_cosine_direction());

	scattered = Ray(rec.pos, unit_vector(direction), r.time);
	alb = albedo->value(rec.u, rec.v, rec.pos);
	pdf = dot(uvw.w(), scattered.direction) / M_PI;

	return true;
}

float Lambertian::scattering_pdf(const Ray& r, const hit_record& rec, const Ray& scattered) const
{
	auto cosine = dot(rec.normal, unit_vector(scattered.direction));
	return cosine < 0 ? 0 : cosine / M_PI;
}