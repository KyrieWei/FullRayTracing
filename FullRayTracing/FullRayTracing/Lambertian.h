#pragma once
#include "Material.h"

class Lambertian : public Material
{
public:
	Vector3D albedo;

	Lambertian(const Vector3D& vec) : albedo(vec) {}

	bool scatter(const Ray& r, const hit_record& rec, Vector3D& attenuation, Ray& scattered) const override;
};

