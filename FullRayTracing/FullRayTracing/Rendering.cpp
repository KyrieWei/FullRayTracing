#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Rendering.h"



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

void Rendering::render(const char* filename, const Camera& camera, const Scene& scene, const Vector3D& background)
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
				color_pixel += rayColor(r, background, scene, maxDepth);
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

Vector3D Rendering::rayColor(const Ray& r, const Vector3D& background, const Scene& scene, int depth)
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

	auto on_light = Vector3D(random_float(213, 343), 554, random_float(227, 332));
	auto to_light = on_light - rec.pos;
	auto distance_squared = length_squared(to_light);
	to_light = unit_vector(to_light);

	if (dot(to_light, rec.normal) < 0)
		return emitted;

	float light_area = (343 - 213) * (332 - 227);
	auto light_cosine = fabs(to_light.y);
	if (light_cosine < 0.000001)
		return emitted;

	pdf = distance_squared / (light_cosine * light_area);
	scattered = Ray(rec.pos, to_light, r.time);

	return emitted + albedo * rec.mat_ptr->scattering_pdf(r, rec, scattered) * rayColor(scattered, background, scene, depth - 1) / pdf;
}

