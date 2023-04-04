#pragma once
#include <vector>
#include "IPolygonCollidable.h"
#include "ICircleCollidable.h"

class SAT 
{
public:
	static bool PolygonPolygonCollision(IPolygonCollidable& polygon1, IPolygonCollidable& polygon2);
	static bool CircleCircleCollision(ICircleCollidable& circle1, ICircleCollidable& circle2);
	static bool PolygonCircleCollision(IPolygonCollidable& polygon, ICircleCollidable& circle);

	static Vector2 GetCollisionNormalPolygon(const IPolygonCollidable& polygon1, const IPolygonCollidable& polygon2);
	static Vector2 GetCollisionNormalCircle(const ICircleCollidable& circle1, const ICircleCollidable& circle2);
	static Vector2 GetCollisionNormalCirclePolygon(const ICircleCollidable& circle, const IPolygonCollidable& polygon);

	static float GetOverlapPolygon(const IPolygonCollidable& polygon1, const IPolygonCollidable& polygon2, const Vector2& axis);
	static float GetOverlapCirclePolygon(const ICircleCollidable& circle, const IPolygonCollidable& polygon, const Vector2& axis);
	
	static void ProjectOntoAxis(const Vector2& axis, const std::vector<Vector2>& vertices, float& min, float& max);
	static void GetUniqueAxes(const std::vector<Vector2>& vertices, std::vector<Vector2>& axes);
	static float DotProduct(const Vector2& a, const Vector2& b) { return a.x * b.x + a.y * b.y; }
	static Vector2 Perpendicular(const Vector2& v1, const Vector2& v2) { return Vector2(v2.y - v1.y, v1.x - v2.x); }
};