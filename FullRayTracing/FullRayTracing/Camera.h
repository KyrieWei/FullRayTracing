#pragma once
#include "Vector3D.h"
#include "Ray.h"
#include <cmath>
#include "Utility.h"


class Camera
{

private:
	Vector3D pos;
	Vector3D lower_left;
	Vector3D horizontal;
	Vector3D vertical;
	Vector3D u, v, w;
	float lens_radius;
	float time0, time1;

public:
	Camera(const Vector3D& lookfrom, const Vector3D& lookat, const Vector3D& vup, const float vfov, const float aspect_ratio, float aperture, float focus_dist, float _time0, float _time1)
	{
		float theta = degrees_to_radians(vfov);
		float h = tan(theta / 2);
		float viewport_height = 2.0 * h;
		float viewport_width = aspect_ratio * viewport_height;  //unit distance without multiplying focus_dist

		//camera space
		w = normalize(lookfrom - lookat); // +Z axis
		u = normalize(cross(vup, w));     // +X axis
		v = cross(w, u);				  // +Y axis

		pos = lookfrom;
		horizontal = focus_dist * viewport_width * u;
		vertical = focus_dist * viewport_height * v;
		lower_left = pos - (horizontal / 2 + vertical / 2 + focus_dist * w);
		
		lens_radius = aperture / 2;
		time0 = _time0;
		time1 = _time1;
	}

	Ray get_ray(float s, float t) const
	{
		Vector3D rd = lens_radius * random_in_unit_disk();
		Vector3D offset = u * rd.x + v * rd.y;

		return Ray(pos + offset, lower_left + s * horizontal + t * vertical - pos - offset, random_float(time0, time1));
	}
};

