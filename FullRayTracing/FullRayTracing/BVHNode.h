#pragma once
#include "Object.h"
#include "Scene.h"

class BVHNode : public Object
{
public:
	shared_ptr<Object> left;
	shared_ptr<Object> right;
	AABB box;

	BVHNode();
	BVHNode(const Scene& scene, float time0, float time1) : BVHNode()

};

