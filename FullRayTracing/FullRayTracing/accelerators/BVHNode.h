#pragma once
#include "../shapes/Object.h"
#include "../scenes/Scene.h"

class BVHNode : public Object
{
public:
	shared_ptr<Object> left;
	shared_ptr<Object> right;
	AABB box;

	BVHNode();
	BVHNode(const std::vector<shared_ptr<Object>>& objects, size_t start, size_t end, float time0, float time1);
	BVHNode(const Scene& scene, float time0, float time1) : BVHNode(scene.objects, 0, scene.objects.size(), time0, time1) {}

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const override;
	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override;
};

