#pragma once
#include "Object.h"
#include "Utility.h"

class Sphere : public Object
{
public:
	Vector3D center;
	float radius;
	shared_ptr<Material> mat_ptr;
	
	Sphere() {}
	Sphere(const Vector3D& _center, float _radius, shared_ptr<Material> _material) : center(_center), radius(_radius), mat_ptr(_material) {}
	Sphere(const Sphere& sphere) : center(sphere.center), radius(sphere.radius), mat_ptr(sphere.mat_ptr) {}

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const override;
	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override;
};


