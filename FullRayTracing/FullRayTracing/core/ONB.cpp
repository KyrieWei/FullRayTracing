#include "ONB.h"
#include "../tools/Utility.h"


void ONB::build_from_w(const Vector3D& n)
{
	axis[2] = unit_vector(n);
	Vector3D a = (fabs(w().x) > 0.9) ? Vector3D(0, 1, 0) : Vector3D(1, 0, 0);
	axis[1] = unit_vector(cross(w(), a));
	axis[0] = cross(w(), v());
}