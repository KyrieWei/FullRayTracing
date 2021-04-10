#pragma once
#include "Vector3D.h"

class Ray
{
public:
	Vector3D origin;
	Vector3D direction;

public:
	Ray();
	~Ray();

	Ray(const Vector3D& _origin, const Vector3D& _direction) : origin(_origin), direction(_direction) {}
	Ray(const Ray& ray) : origin(ray.origin), direction(ray.direction) {}

	Vector3D pointAt(const float t) const { return origin + t * direction; }
};

