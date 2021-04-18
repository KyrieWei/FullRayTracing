#pragma once
#include "Object.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class Scene : public Object
{
public:
	std::vector<shared_ptr<Object>> objects;

	Scene() {}
	Scene(shared_ptr<Object> obj) { add(obj); }

	void add(shared_ptr<Object> obj)
	{
		objects.push_back(obj);
	}

	void clear()
	{
		objects.clear();
	}

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override;
};



