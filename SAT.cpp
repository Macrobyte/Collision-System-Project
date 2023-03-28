#include "SAT.h"


//bool SAT::Collides(const ICollidable& shape1, const ICollidable& shape2)
//{
//    std::vector<Vector2> vertices1 = shape1.GetVertices();
//    std::vector<Vector2> vertices2 = shape2.GetVertices();
//    std::vector<Vector2> normals1 = shape1.GetNormals();
//    std::vector<Vector2> normals2 = shape2.GetNormals();
//
//    if (dynamic_cast<const Circle*>(&shape1) || dynamic_cast<const Circle*>(&shape2))
//    {
//        const Circle* circle = dynamic_cast<const Circle*>(&shape1);
//        const ICollidable* otherShape = &shape2;
//        if (!circle) {
//            circle = dynamic_cast<const Circle*>(&shape2);
//            otherShape = &shape1;
//        }
//        if (!circle->Collides(*otherShape)) {
//            return false;
//        }
//    }
//    else
//    {
//        for (const auto& normal : normals1) {
//            float min1, max1, min2, max2;
//            ProjectOntoAxis(normal, vertices1, min1, max1);
//            ProjectOntoAxis(normal, vertices2, min2, max2);
//            if (max1 < min2 || max2 < min1) {
//                return false;
//            }
//        }
//
//        for (const auto& normal : normals2) {
//            float min1, max1, min2, max2;
//            ProjectOntoAxis(normal, vertices1, min1, max1);
//            ProjectOntoAxis(normal, vertices2, min2, max2);
//            if (max1 < min2 || max2 < min1) {
//                return false;
//            }
//        }
//    }
//
//	return true;
//}

bool SAT::PolygonPolygonCollision(const IPolygonCollidable& polygon1, const IPolygonCollidable& polygon2)
{
    std::vector<Vector2> vertices1 = polygon1.GetVertices();
    std::vector<Vector2> vertices2 = polygon2.GetVertices();
    std::vector<Vector2> normals1 = polygon1.GetNormals();
    std::vector<Vector2> normals2 = polygon2.GetNormals();

    for (const auto& normal : normals1) {
        float min1, max1, min2, max2;
        ProjectOntoAxis(normal, vertices1, min1, max1);
        ProjectOntoAxis(normal, vertices2, min2, max2);
        if (max1 < min2 || max2 < min1) {
            return false;
        }
    }

    for (const auto& normal : normals2) {
        float min1, max1, min2, max2;
        ProjectOntoAxis(normal, vertices1, min1, max1);
        ProjectOntoAxis(normal, vertices2, min2, max2);
        if (max1 < min2 || max2 < min1) {
            return false;
        }
    }

    return true;       	
}

bool SAT::CircleCircleCollision(const ICircleCollidable& circle1, const ICircleCollidable& circle2)
{
    float distance = (circle1.GetPosition() - circle2.GetPosition()).magnitude();
    float radiusSum = circle1.GetRadius() + circle2.GetRadius();

    return distance < radiusSum;
}

bool SAT::PolygonCircleCollision(const IPolygonCollidable& polygon, const ICircleCollidable& circle)
{
    const std::vector<Vector2>& polygonVertices = polygon.GetVertices();
    Vector2 circlePosition = circle.GetPosition();
    float circleRadius = circle.GetRadius();

    for (int i = 0; i < polygonVertices.size(); ++i)
    {
        Vector2 axis;
        if (i == polygonVertices.size() - 1)
        {
            axis = (polygonVertices[0] - polygonVertices[i]).perp().normalize();
        }
        else
        {
            axis = (polygonVertices[i + 1] - polygonVertices[i]).perp().normalize();
        }

        float minProj1 = std::numeric_limits<float>::max();
        float maxProj1 = std::numeric_limits<float>::min();

        for (const Vector2& vertex : polygonVertices)
        {
            float projection = dot(vertex, axis);
            if (projection < minProj1) minProj1 = projection;
            if (projection > maxProj1) maxProj1 = projection;
        }

        float minProj2 = dot(circlePosition, axis) - circleRadius;
        float maxProj2 = dot(circlePosition, axis) + circleRadius;

        if (maxProj2 < minProj1 || maxProj1 < minProj2)
        {
            return false;
        }
    }

    return true;
}

void SAT::ProjectOntoAxis(const Vector2& axis, const std::vector<Vector2>& vertices, float& min, float& max)
{
    min = std::numeric_limits<float>::max();
    max = std::numeric_limits<float>::lowest();
    for (const auto& vertex : vertices) {
        float projection = dot(axis, vertex);
        min = std::min(min, projection);
        max = std::max(max, projection);
    }
}
