#pragma once
#include "Object.h"

struct hit_record;

class Material
{
public:
	virtual bool scatter(const Ray& r, const hit_record& rec, Vector3D& albedo, Ray& scattered, float& pdf) const
	{
		return false;
	}

	virtual float scattering_pdf(const Ray& r, const hit_record& rec, const Ray& scattered) const
	{
		return 0;
	}

	virtual Vector3D emitted(const Ray& r_in, const hit_record& rec, float u, float v, const Vector3D& p) const
	{
		return Vector3D(0, 0, 0);
	}
};

