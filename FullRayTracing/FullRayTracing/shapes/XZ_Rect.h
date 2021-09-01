#pragma once
#include "Object.h"
class XZ_Rect : public Object
{
public:
	XZ_Rect() {}

	XZ_Rect(float _x0, float _x1, float _z0, float _z1, float _k, shared_ptr<Material> mat) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) {}

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override
	{
		output_box = AABB(Vector3D(x0, k - 0.0001, z0), Vector3D(x1, k + 0.0001, z1));
		return true;
	}

	virtual float pdf_value(const Vector3D& origin, const Vector3D& v) const override
	{
		hit_record rec;
		if (!this->hit(Ray(origin, v), rec, 0.001, INFINITY))
			return 0;

		auto area = (x1 - x0) * (z1 - z0);
		auto distance_squared = rec.t * rec.t * length_squared(v);
		auto cosine = fabs(dot(v, rec.normal) / length(v));

		return distance_squared / (cosine * area);
	}

	virtual Vector3D random(const Vector3D& origin) const override
	{
		auto random_point = Vector3D(random_float(x0, x1), k, random_float(z0, z1));
		return random_point - origin;
	}

public:
	shared_ptr<Material> mp;
	float x0, x1, z0, z1, k;
};

