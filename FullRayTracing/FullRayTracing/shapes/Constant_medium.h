#pragma once
#include "Object.h"
#include "../textures/Texture.h"
#include "../materials/Isotropic.h"

class Constant_medium : public Object
{
public:
	shared_ptr<Object> boundary;
	shared_ptr<Material> phase_function;
	float neg_inv_density;

public:
	Constant_medium(shared_ptr<Object> b, float d, shared_ptr<Texture> a) : boundary(b), neg_inv_density(-1 / d), phase_function(std::make_shared<Isotropic>(a)) {}
	Constant_medium(shared_ptr<Object> b, float d, Vector3D c) : boundary(b), neg_inv_density(-1 / d), phase_function(std::make_shared<Isotropic>(c)) {}

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override
	{
		return boundary->bounding_box(time0, time1, output_box);
	}
	
};

