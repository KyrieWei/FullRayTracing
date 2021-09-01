#pragma once
#include "../maths/Vector3D.h"
#include "../shapes/Ray.h"

class AABB
{
public:
	Vector3D minimum;
	Vector3D maximum;

	AABB() {}
	AABB(const Vector3D& _max, const Vector3D& _min) : maximum(_max), minimum(_min) {}

	bool hit(const Ray& r, float t_min, float t_max) const;

};

