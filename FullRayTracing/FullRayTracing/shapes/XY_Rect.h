#pragma once
#include "Object.h"

class XY_Rect : public Object
{
public:
	XY_Rect();

	XY_Rect(float _x0, float _x1, float _y0, float _y1, float _k, shared_ptr<Material> mat) :
		x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {}

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override
	{
		output_box = AABB(Vector3D(x0, y0, k - 0.0001), Vector3D(x1, y1, k + 0.0001));
		return true;
	}

public:
	shared_ptr<Material> mp;
	//k为另一维度的值
	float x0, x1, y0, y1, k;
};

