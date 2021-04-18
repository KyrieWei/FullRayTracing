#pragma once
#include "Vector3D.h"

class Ray
{
public:
	Vector3D origin;
	Vector3D direction;
	float time;

public:
	Ray();
	~Ray();

	Ray(const Vector3D& _origin, const Vector3D& _direction, float _time = 0.0) : origin(_origin), direction(_direction), time(_time) {}
	Ray(const Ray& ray) : origin(ray.origin), direction(ray.direction), time(ray.time) {}

	Vector3D pointAt(const float t) const { return origin + t * direction; }
};

