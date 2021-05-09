#include "BVHNode.h"
#include <algorithm>

inline bool box_compare(const shared_ptr<Object> a, const shared_ptr<Object> b, int axis)
{
	AABB box_a;
	AABB box_b;

	if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
		std::cerr << "No bounding box in bvh_node constructor.\n";

	return box_a.minimum[axis] < box_b.minimum[axis];
}

bool box_x_compare(const shared_ptr<Object> a, const shared_ptr<Object> b)
{
	return box_compare(a, b, 0);
}

bool box_y_compare(const shared_ptr<Object> a, const shared_ptr<Object> b)
{
	return box_compare(a, b, 1);
}

bool box_z_compare(const shared_ptr<Object> a, const shared_ptr<Object> b)
{
	return box_compare(a, b, 2);
}

BVHNode::BVHNode(const std::vector<shared_ptr<Object>>& objects, size_t start, size_t end, float time0, float time1)
{
	auto m_objects = objects;

	int axis = random_int(0, 2);

	auto comparator = (axis == 0) ? box_x_compare : (axis == 1) ? box_y_compare : box_z_compare;

	size_t object_span = end - start;

	if (object_span == 1)
	{
		left = right = m_objects[start];
	}
	else if(object_span == 2)
	{
		if (comparator(m_objects[start], m_objects[start + 1]))
		{
			left = m_objects[start];
			right = m_objects[start + 1];
		}
		else
		{
			left = m_objects[start + 1];
			right = m_objects[start];
		}
	}
	else
	{
		std::sort(m_objects.begin() + start, m_objects.begin() + end, comparator);

		auto mid = start + object_span / 2;

		left = make_shared<BVHNode>(m_objects, start, mid, time0, time1);
		right = make_shared<BVHNode>(m_objects, mid, end, time0, time1);
	}

	AABB box_left, box_right;

	if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
		std::cerr << "No bounding box in BVHNode constructor.\n";

	box = surrounding_box(box_left, box_right);
}

bool BVHNode::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	if (!box.hit(r, t_min, t_max))
		return false;

	bool hit_left = left->hit(r, rec, t_min, t_max);
	bool hit_right = right->hit(r, rec, t_min, hit_left ? rec.t : t_max);

	return hit_left || hit_right;
}

bool BVHNode::bounding_box(float time0, float time1, AABB& output_box) const
{
	output_box = box;
	return true;
}
