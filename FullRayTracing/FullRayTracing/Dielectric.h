#pragma once
#include "Material.h"

class Dielectric : public Material
{
public:
	float ir;

	Dielectric(float index_of_refraction) : ir(index_of_refraction) {}

	virtual bool scatter(const Ray& r, const hit_record& rec, Vector3D& attenuation, Ray& scattered) const override;

};

