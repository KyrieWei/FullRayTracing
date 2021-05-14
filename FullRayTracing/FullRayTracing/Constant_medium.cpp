#include "Constant_medium.h"

bool Constant_medium::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	const bool enableDebug = false;
	const bool debugging = enableDebug && random_float() < 0.00001;

	hit_record rec1, rec2;

	if (!boundary->hit(r, rec, -INFINITY, INFINITY))
		return false;

	if (!boundary->hit(r, rec2, rec1.t + 0.0001, INFINITY))
		return false;

	if (debugging) std::cerr << "\nt_min = " << rec.t << ", t_max = " << rec2.t << ".\n";

	if (rec1.t < t_min) rec1.t = t_min;
	if (rec2.t > t_max) rec2.t = t_max;

	if (rec1.t >= rec2.t)
		return false;

	if (rec1.t < 0)
		rec1.t = 0;
	

	const auto ray_length = length(r.direction);
	const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
	const auto hit_distance = neg_inv_density * log(random_float());

	if (hit_distance > distance_inside_boundary)
		return false;

	rec.t = rec1.t + hit_distance / ray_length;
	rec.pos = r.pointAt(rec.t);

	if (debugging) {
		std::cerr << "hit_distance = " << hit_distance << '\n'
			<< "rec.t = " << rec.t << '\n'
			<< "rec.p = " << rec.p << '\n';
	}

	rec.normal = Vector3D(1, 0, 0);
	rec.front_face = true;
	rec.mat_ptr = phase_function;

	return true;
}