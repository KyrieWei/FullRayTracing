#include "Dielectric.h"

bool Dielectric::scatter(const Ray& r, const hit_record& rec, Vector3D& attenuation, Ray& scattered) const
{
	attenuation = Vector3D(1.0, 1.0, 1.0);
	float refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

	Vector3D unit_direction = unit_vector(r.direction);
	float cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
	float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.0;
	Vector3D direction;

	if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_float())
		direction = reflect(unit_direction, rec.normal);
	else
		direction = refract(unit_direction, rec.normal, refraction_ratio);


	scattered = Ray(rec.pos, direction, r.time);
	return true;
}
