#pragma once
#include "Object.h"

class Material
{
public:
	virtual bool scatter(const Ray& r, const hit_record& rec, Vector3D& attenuation, Ray& scattered) const = 0;

};

