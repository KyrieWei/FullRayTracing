#include <iostream>

#include "Rendering.h"
#include "Camera.h"




int main()
{
	const char* filename = "../result/test.jpg";

	const int width = 1280;
	const int height = 720;
	const int channel = 4;
	const int depth = 50;

	Vector3D camera_pos(0, 0, 0);
	Vector3D camera_lookat(0, 0, -1);
	Vector3D camera_up(0, 1, 0);
	float vfov = 45;
	float focal_dist = 10;
	float aspect_ratio = float(width) / height;

	Camera camera(camera_pos, camera_lookat, camera_up, vfov, aspect_ratio, focal_dist);

	Rendering render;
	render.initialize(width, height, channel, depth);
	render.render(filename, camera);



	return 0;
}