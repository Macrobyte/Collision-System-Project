#pragma once
#include <vector>
#include "IPolygonCollidable.h"
#include "ICircleCollidable.h"

class SAT 
{
public:
	static bool PolygonPolygonCollision(const IPolygonCollidable& polygon1, const IPolygonCollidable& polygon2);
	static bool CircleCircleCollision(const ICircleCollidable& circle1, const ICircleCollidable& circle2);
	static bool PolygonCircleCollision(const IPolygonCollidable& polygon, const ICircleCollidable& circle);

private:
	static void ProjectOntoAxis(const Vector2& axis, const std::vector<Vector2>& vertices, float& min, float& max);
	static void GetUniqueAxes(const std::vector<Vector2>& vertices, std::vector<Vector2>& axes);
	static float DotProduct(const Vector2& a, const Vector2& b) { return a.x * b.x + a.y * b.y; }
};