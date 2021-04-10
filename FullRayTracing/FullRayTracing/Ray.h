#pragma once
#include "Vector3D.h"

class Ray
{
private:
	Vector3D m_origin;
	Vector3D m_direction;

public:
	Ray();
	~Ray();

	Ray(const Vector3D& _origin, const Vector3D& _direction) : m_origin(_origin), m_direction(_direction) {}
	Ray(const Ray& ray) : m_origin(ray.m_origin), m_direction(ray.m_direction) {}

	Vector3D getOrigin() const { return m_origin; }
	Vector3D getDIreciton() const { return m_direction; }

	Vector3D pointAt(const float t) const { return m_origin + t * m_direction; }
};

