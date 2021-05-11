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

public:
	shared_ptr<Material> mp;
	float x0, x1, z0, z1, k;
};

