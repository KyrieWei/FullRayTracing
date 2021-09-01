#pragma once
#include "Material.h"
#include "../textures/Texture.h"

class Diffuse_light : public Material
{
public:
	Diffuse_light(shared_ptr<Texture> a) : emit(a) {}
	Diffuse_light(Vector3D c) : emit(std::make_shared<solid_color>(c)) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vector3D& attenuation, Ray& scattered) const override
	{
		return false;
	}

	virtual Vector3D emitted(const Ray& r_in, const hit_record& rec, float u, float v, const Vector3D& p) const override
	{
		if (rec.front_face)
			return emit->value(u, v, p);
		else
			return Vector3D(0, 0, 0);
	}

public:
	shared_ptr<Texture> emit;

};

