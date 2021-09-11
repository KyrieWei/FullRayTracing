#include "Box.h"
#include "XY_Rect.h"
#include "YZ_Rect.h"
#include "XZ_Rect.h"

Box::Box(const Vector3D& p0, const Vector3D& p1, shared_ptr<Material> ptr)
{
	box_min = p0;
	box_max = p1;

	//λ��Z�Ḻ�������
	sides.add(make_shared<XY_Rect>(p0.x, p1.x, p0.y, p1.y, p1.z, ptr));
	//λ��Z�����������
	sides.add(make_shared<XY_Rect>(p0.x, p1.x, p0.y, p1.y, p0.z, ptr));
	//λ��Y�����������
	sides.add(make_shared<XZ_Rect>(p0.x, p1.x, p0.z, p1.z, p1.y, ptr));
	//λ��Y�Ḻ�������
	sides.add(make_shared<XZ_Rect>(p0.x, p1.x, p0.z, p1.z, p0.y, ptr));
	//λ��X�����������
	sides.add(make_shared<YZ_Rect>(p0.y, p1.y, p0.z, p1.z, p1.x, ptr));
	//λ��X�Ḻ�������
	sides.add(make_shared<YZ_Rect>(p0.y, p1.y, p0.z, p1.z, p0.x, ptr));

}

bool Box::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	return sides.hit(r, rec, t_min, t_max);
}