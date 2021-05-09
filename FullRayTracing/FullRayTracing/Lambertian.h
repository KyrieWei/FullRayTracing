#pragma once
#include "Material.h"
#include "Texture.h"

class Lambertian : public Material
{
public:
	shared_ptr<Texture> albedo;

	Lambertian(const Vector3D& a) : albedo(std::make_shared<solid_color>(a)) {}
	Lambertian(shared_ptr<Texture> a) : albedo(a) {}

	bool scatter(const Ray& r, const hit_record& rec, Vector3D& attenuation, Ray& scattered) const override;
};

