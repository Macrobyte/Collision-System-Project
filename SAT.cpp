#include "SAT.h"

bool SAT::PolygonPolygonCollision(const IPolygonCollidable& polygon1, const IPolygonCollidable& polygon2)
{
    std::vector<Vector2> axes;
    std::vector<Vector2> vertices1 = polygon1.GetVertices();
    std::vector<Vector2> vertices2 = polygon2.GetVertices();

    // Get all the unique axes
    GetUniqueAxes(vertices1, axes);
    GetUniqueAxes(vertices2, axes);

    // Project the vertices onto each axis and check for overlap
    for (const auto& axis : axes) {
        float min1, max1, min2, max2;
        ProjectOntoAxis(axis, vertices1, min1, max1);
        ProjectOntoAxis(axis, vertices2, min2, max2);

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
            float projection = DotProduct(vertex, axis);
            if (projection < minProj1) minProj1 = projection;
            if (projection > maxProj1) maxProj1 = projection;
        }

        float minProj2 = DotProduct(circlePosition, axis) - circleRadius;
        float maxProj2 = DotProduct(circlePosition, axis) + circleRadius;

        if (maxProj2 < minProj1 || maxProj1 < minProj2)
        {
            return false;
        }
    }

    return true;
}

void SAT::ProjectOntoAxis(const Vector2& axis, const std::vector<Vector2>& vertices, float& min, float& max)
{
    float dot_product = DotProduct(vertices[0], axis);
    min = dot_product;
    max = dot_product;
    for (size_t i = 1; i < vertices.size(); i++) {
        dot_product = DotProduct(vertices[i], axis);
        if (dot_product < min) {
            min = dot_product;
        }
        else if (dot_product > max) {
            max = dot_product;
        }
    }
}

void SAT::GetUniqueAxes(const std::vector<Vector2>& vertices, std::vector<Vector2>& axes)
{
    for (size_t i = 0; i < vertices.size(); i++) {
        size_t j = (i + 1) % vertices.size();
        Vector2 edge = vertices[j] - vertices[i];
        Vector2 normal(-edge.y, edge.x);
        normal.normalize();

        bool is_unique = true;
        for (const auto& axis : axes) {
            if (DotProduct(axis, normal) > 0.99f || DotProduct(axis, -normal) > 0.99f) {
                is_unique = false;
                break;
            }
        }
        if (is_unique) {
            axes.push_back(normal);
        }
    }
}
