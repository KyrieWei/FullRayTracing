#pragma once
#include "Vector4D.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"

class Rendering
{

	int width, height, channel, maxDepth, samples_per_pixel;

	unsigned char* m_image;

	

public:
	Rendering() {};
	~Rendering()
	{
		delete[] m_image;
	}

	void initialize(int w, int h, int c = 4, int depth = 50, int _samples_per_pixel = 100);

	void render(const char* filename, const Camera& camera, const Scene& scene, const Vector3D& background);

	void drawPixel(int x, int y, const Vector3D& color);

	Vector3D rayColor(const Ray& r, const Vector3D& background, const Scene& scene, int depth);

};

