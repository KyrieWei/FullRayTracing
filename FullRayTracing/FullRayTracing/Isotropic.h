#pragma once
#include "Material.h"
#include "Texture.h"

class Isotropic : public Material
{
public:
	shared_ptr<Texture> albedo;

public:
	Isotropic(Vector3D c) : albedo(std::make_shared<solid_color>(c)) {}
	Isotropic(shared_ptr<Texture> a) : albedo(a) {}

	virtual bool scatter(const Ray& r, const hit_record& rec, Vector3D& attenuation, Ray& scattered, float& pdf) const override
	{
		scattered = Ray(rec.pos, random_in_unit_sphere(), r.time);
		attenuation = albedo->value(rec.u, rec.v, rec.pos);

		return true;
	}
};

