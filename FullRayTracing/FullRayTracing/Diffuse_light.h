#pragma once
#include "Material.h"
#include "Texture.h"

class Diffuse_light : public Material
{
public:
	Diffuse_light(shared_ptr<Texture> a) : emit(a) {}
	Diffuse_light(Vector3D c) : emit(std::make_shared<solid_color>(c)) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vector3D& attenuation, Ray& scattered) const override
	{
		return false;
	}

	virtual Vector3D emitted(float u, float v, const Vector3D& p) const override
	{
		return emit->value(u, v, p);
	}

public:
	shared_ptr<Texture> emit;

};

