#pragma once
#include "Vector3D.h"

class ONB
{
public:
	Vector3D axis[3];

public:
	ONB() {}

	inline Vector3D operator[](int i) const { return axis[i]; }

	Vector3D u() const { return axis[0]; }
	Vector3D v() const { return axis[1]; }
	Vector3D w() const { return axis[2]; }

	Vector3D local(float a, float b, float c) const
	{
		return a * u() + b * v() + c * w();
	}

	Vector3D local(const Vector3D& a) const
	{
		return a.x * u() + a.y * v() + a.z * w();
	}

	void build_from_w(const Vector3D& n);

};

