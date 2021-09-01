#pragma once
#include "Object.h"
class YZ_Rect : public Object
{
public:
	YZ_Rect() {}

	YZ_Rect(float _y0, float _y1, float _z0, float _z1, float _k, shared_ptr<Material> mat) :
		y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {}

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override
	{
		output_box = AABB(Vector3D(k - 0.0001, y0, z0), Vector3D(k + 0.0001, y1, z1));
		return true;
	}

public:
	shared_ptr<Material> mp;
	float y0, y1, z0, z1, k;
};

