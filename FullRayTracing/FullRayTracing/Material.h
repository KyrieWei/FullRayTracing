#pragma once
#include "Object.h"

struct hit_record;

class Material
{
public:
	virtual bool scatter(const Ray& r, const hit_record& rec, Vector3D& attenuation, Ray& scattered) const = 0;
	virtual Vector3D emitted(float u, float v, const Vector3D& p) const
	{
		return Vector3D(0, 0, 0);
	}
};

