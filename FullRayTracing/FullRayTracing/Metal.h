#pragma once
#include "Material.h"

class Metal : public Material
{
public:
	Vector3D albedo;
	float fuzz;

	Metal(const Vector3D& a, float f) : albedo(a), fuzz(f < 1 ? f : 1){}

	virtual bool scatter(const Ray& r, const hit_record& rec, Vector3D& attenuation, Ray& scattered) const override;
};

