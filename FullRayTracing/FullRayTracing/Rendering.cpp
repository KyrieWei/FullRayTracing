#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Rendering.h"
#include "Cosine_pdf.h"
#include "Object_PDF.h"
#include "Mixture_PDF.h"


void Rendering::initialize(int w, int h, int c, int depth, int _samples_per_pixel)
{
	width = w;
	height = h;
	channel = c;
	maxDepth = depth;
	samples_per_pixel = _samples_per_pixel;

	if (m_image != nullptr)
		delete[] m_image;

	m_image = new unsigned char[width * height * channel];
}

void Rendering::render(const char* filename, const Camera& camera, const Scene& scene, shared_ptr<Object>& lights, const Vector3D& background)
{

	for (int row = height - 1; row >= 0; row--)
	{
		std::cerr << "\rScanlines remaining: " << row << ' ' << std::flush;
		for (int col = 0; col < width; col++)
		{
			Vector3D color_pixel(0, 0, 0);
			for (int i = 0; i < samples_per_pixel; i++)
			{
				float s = (col + random_float()) / width;
				float t = (row + random_float()) / height;

				Ray r = camera.get_ray(s, t);
				color_pixel += rayColor(r, background, scene, lights, maxDepth);
			}
			
			drawPixel(row, col, color_pixel);
		}
	}

	stbi_write_jpg(filename, width, height, channel, m_image, 100);

}

void Rendering::drawPixel(int row, int col, const Vector3D& color)
{
	if (row < 0 || row >= height || col < 0 || col >= width)
		return;

	float scale = float(1) / samples_per_pixel;

	float r = m_clamp(sqrt(color.x * scale), 0.0, 0.999);
	float g = m_clamp(sqrt(color.y * scale), 0.0, 0.999);
	float b = m_clamp(sqrt(color.z * scale), 0.0, 0.999);

	unsigned int index = ((height - row - 1) * width + col) * channel;
	m_image[index] = static_cast<unsigned char>(r * 255);
	m_image[index + 1] = static_cast<unsigned char>(g * 255);
	m_image[index + 2] = static_cast<unsigned char>(b * 255);
	m_image[index + 3] = static_cast<unsigned char>(255);
}

Vector3D Rendering::rayColor(const Ray& r, const Vector3D& background, const Scene& scene, shared_ptr<Object>& lights, int depth)
{
	hit_record rec;

	if (depth <= 0)
		return Vector3D(0, 0, 0);

	if (!scene.hit(r, rec, 0.001, INFINITY))
		return background;

	Ray scattered;
	Vector3D attenuation;
	Vector3D emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.pos);
	float pdf;
	Vector3D albedo;
	
	if (!rec.mat_ptr->scatter(r, rec, albedo, scattered, pdf))
		return emitted;

	auto p0 = make_shared<Object_PDF>(lights, rec.pos);
	auto p1 = make_shared<Cosine_pdf>(rec.normal);
	Mixture_PDF mixed_pdf(p0, p1);

	scattered = Ray(rec.pos, mixed_pdf.generate(), r.time);
	pdf = mixed_pdf.value(scattered.direction);
	

	return emitted + albedo * rec.mat_ptr->scattering_pdf(r, rec, scattered) * rayColor(scattered, background, scene, lights, depth - 1) / pdf;
}

