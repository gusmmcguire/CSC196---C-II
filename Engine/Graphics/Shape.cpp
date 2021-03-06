#include "Shape.h"
#include <fstream>
#include <algorithm>

namespace gme{
	void Shape::Draw(Core::Graphics& graphics, const Vector2& position, float angle, float scale){
		graphics.SetColor(color);
		for (size_t i = 0; i < points.size() - 1; i++) {
			Vector2 p1 = (position + (Vector2::Rotate(points[i],angle) * scale));
			Vector2 p2 = (position + (Vector2::Rotate(points[i + 1],angle) * scale));
			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	void Shape::Draw(Core::Graphics& graphics, const Transform& transform){
		graphics.SetColor(color);
		for (size_t i = 0; i < points.size() - 1; i++) {
			Vector2 p1 = transform.matrix*points[i];
			Vector2 p2 = transform.matrix*points[i+1];
			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	bool Shape::Load(const std::string& filename){
		bool success = false;

		std::ifstream stream{ filename };
		if (stream.is_open()) {
			success = true;

			stream >> color;

			std::string line;
			std::getline(stream, line);
			size_t size = std::stoi(line);
			for (size_t i = 0; i < size; i++) {
				Vector2 point;
				stream >> point;
				points.push_back(point);
			}
			ComputeRadius();
			ComputeCorner();
			ComputeWidth();
			ComputeHeight();
		}

		
		return success;
	}
	
	void Shape::ComputeRadius(){
		for (Vector2& point : points) {
			radius = std::max(radius, point.Length());
		}
		//std::for_each(points.begin(), points.end(), [radius](auto& point) {radius = std::max(radius, point.Length()); });
	}

	void Shape::ComputeWidth() {
		float x = points[0].x;
		for (int q = 0; q < points.size(); q++) {
			if (points[q].x > x) x = points[q].x;
		}
		width = x - topLeftCorner.x;
	}

	void Shape::ComputeHeight(){
		float y = points[0].y;
		for (int q = 0; q < points.size(); q++) {
			if (points[q].y > y) y = points[q].y;
		}
		height = y - topLeftCorner.y;
	}

	void Shape::ComputeCorner(){
		float leftX = points[0].x;
		for (int q = 0; q < points.size(); q++) {
			if (points[q].x < leftX) leftX = points[q].x;
		}

		float topY = points[0].y;
		for (int q = 0; q < points.size(); q++) {
			if (points[q].y < topY) topY = points[q].y;
		}

		topLeftCorner = { leftX, topY };
	}
}