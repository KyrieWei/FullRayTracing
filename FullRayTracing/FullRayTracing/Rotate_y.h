#pragma once
#include "Object.h"
class Rotate_y : public Object 
{
public:
	shared_ptr<Object> ptr;
	float sin_theta;
	float cos_theta;
	bool hasbox;
	AABB bbox;

public:
	Rotate_y(shared_ptr<Object> p, float angle);

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override
	{
		output_box = bbox;
		return hasbox;
	}
};

