#include "BVHNode.h"

BVHNode::BVHNode(const Scene& scene, float time0, float time1)
{

}

bool BVHNode::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	if (!box.hit(r, t_min, t_max))
		return false;

	bool hit_left = left->hit(r, rec, t_min, t_max);
	bool hit_right = right->hit(r, rec, t_min, hit_left ? rec.t : t_max);

	return hit_left || hit_right;
}