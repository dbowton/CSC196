#include "Shape.h"
#include <fstream>

namespace dwb
{
	void Shape::Draw(Core::Graphics& graphics, const Vector2& position, float angle, float scale)
	{
		graphics.SetColor(color);

		for (size_t i = 0; i < points.size() - 1; i++) {
			dwb::Vector2 p1 = position + (Vector2::Rotate(points[i], angle) * scale);
			dwb::Vector2 p2 = position + (Vector2::Rotate(points[i + 1], angle) * scale);

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Shape::Draw(Core::Graphics& graphics, const Transform& transform)
	{
		graphics.SetColor(color);

		for (size_t i = 0; i < points.size() - 1; i++) {
			dwb::Vector2 p1 = transform.matrix * points[i];
			dwb::Vector2 p2 = transform.matrix * points[i + 1];

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	bool Shape::Load(const std::string& fileName)
	{
		bool success = false;

		std::ifstream stream(fileName);
		if (stream.is_open())
		{
			success = true;
			
			stream >> color;

			std::string line;
			std::getline(stream, line);
			size_t size = std::stoi(line);

			for (size_t i = 0; i < size; i++)
			{
				dwb::Vector2 point;
				stream >> point;

				points.push_back(point);
			}

			ComputeRadius();
		}

		return success;
	}

	void Shape::ComputeRadius()
	{
		for (auto& point : points)
		{
			radius = std::max(radius, point.Length());
		}
	}
}
