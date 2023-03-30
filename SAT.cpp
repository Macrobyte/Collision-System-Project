#include "SAT.h"

bool SAT::PolygonPolygonCollision(IPolygonCollidable& polygon1, IPolygonCollidable& polygon2)
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

bool SAT::CircleCircleCollision(ICircleCollidable& circle1, ICircleCollidable& circle2)
{
    float distance = (circle1.GetPosition() - circle2.GetPosition()).magnitude();
    float radiusSum = circle1.GetRadius() + circle2.GetRadius();

    return distance < radiusSum;
}

bool SAT::PolygonCircleCollision(IPolygonCollidable& polygon, ICircleCollidable& circle)
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

Vector2 SAT::GetCollisionNormalPolygon(const IPolygonCollidable& polygon1, const IPolygonCollidable& polygon2)
{
    std::vector<Vector2> axes1 = polygon1.GetNormals();
    std::vector<Vector2> axes2 = polygon2.GetNormals();

    std::vector<Vector2> vertices1 = polygon1.GetVertices();
    std::vector<Vector2> vertices2 = polygon2.GetVertices();

    // Combine the axes of both polygons
    std::vector<Vector2> axes;
    axes.insert(axes.end(), axes1.begin(), axes1.end());
    axes.insert(axes.end(), axes2.begin(), axes2.end());

    // Initialize minimum overlap and collision normal
    float minOverlap = std::numeric_limits<float>::max();
    Vector2 collisionNormal;

    // Project vertices of both polygons onto each axis
    for (const auto& axis : axes)
    {
        float min1 = std::numeric_limits<float>::max();
        float max1 = std::numeric_limits<float>::min();
        float min2 = std::numeric_limits<float>::max();
        float max2 = std::numeric_limits<float>::min();

        // Project vertices of polygon 1 onto the current axis
        for (const auto& vertex : vertices1)
        {
            float projection = DotProduct(vertex, axis);
            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        // Project vertices of polygon 2 onto the current axis
        for (const auto& vertex : vertices2)
        {
            float projection = DotProduct(vertex, axis);
            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        // Check for overlap on the current axis
        float overlap = std::max(0.0f, std::min(max1, max2) - std::max(min1, min2));

        // If there is no overlap on the current axis, the polygons do not collide
        if (overlap == 0.0f)
        {
            return Vector2(0,0);
        }

        // If the overlap on the current axis is the smallest so far, set it as the new minimum overlap
        if (overlap < minOverlap)
        {
            minOverlap = overlap;
            collisionNormal = axis;
        }
    }

    // If we get here, the polygons must be colliding
    return collisionNormal;
}

Vector2 SAT::GetCollisionNormalCircle(const ICircleCollidable& circle1, const ICircleCollidable& circle2)
{
    Vector2 center1 = circle1.GetPosition();
    Vector2 center2 = circle2.GetPosition();
    float radius1 = circle1.GetRadius();
    float radius2 = circle2.GetRadius();

    Vector2 collisionNormal = center2 - center1;

    float distance = collisionNormal.magnitude();

    if (distance == 0) {
        // The circles are overlapping
        return Vector2(1, 0); // Return an arbitrary normal vector
    }

    collisionNormal.magnitude();

    float overlap = radius1 + radius2 - distance;

    if (overlap < 0) {
        // The circles are not overlapping
        return Vector2(0, 0);
    }

    return collisionNormal * overlap;
}

Vector2 SAT::GetCollisionNormalCirclePolygon(const ICircleCollidable& circle, const IPolygonCollidable& polygon)
{
    std::vector<Vector2> axes;
    std::vector<Vector2> vertices = polygon.GetVertices();

    // Get all the unique axes
    GetUniqueAxes(vertices, axes);

    // Add the axis perpendicular to the circle's center to the circle's center-to-vertex axes
    Vector2 centerToCircle = circle.GetPosition() - polygon.GetPosition();
    axes.push_back(centerToCircle);
    for (const auto& vertex : vertices) {
        axes.push_back(Perpendicular(centerToCircle, vertex - polygon.GetPosition()));
    }

    // Project the vertices and the circle's center onto each axis and check for overlap
    float minOverlap = std::numeric_limits<float>::max();
    Vector2 collisionNormal;
    for (const auto& axis : axes) {
        float min1, max1, min2, max2;
        ProjectOntoAxis(axis, vertices, min1, max1);
        float circleProjection = DotProduct(circle.GetPosition(), axis);
        min2 = circleProjection - circle.GetRadius();
        max2 = circleProjection + circle.GetRadius();

        if (max1 < min2 || max2 < min1) {
            return Vector2::Zero();  // No collision
        }

        // Calculate overlap
        float overlap = std::min(max1, max2) - std::max(min1, min2);
        if (overlap < minOverlap) {
            minOverlap = overlap;
            collisionNormal = axis;
        }
    }

    // If the circle's center is inside the polygon, return the projection onto the axis perpendicular to the collision normal
    if (minOverlap == 0 && DotProduct(centerToCircle, collisionNormal) > 0) {
        collisionNormal = Perpendicular(collisionNormal, centerToCircle);
    }

    return collisionNormal.normalized();
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

float SAT::GetOverlapPolygonPolygon(const IPolygonCollidable& polygon1, const IPolygonCollidable& polygon2, const Vector2& axis)
{
    // Project the vertices of both polygons onto the axis
    std::vector<Vector2> vertices1 = polygon1.GetVertices();
    std::vector<Vector2> vertices2 = polygon2.GetVertices();
    float min1, max1, min2, max2;
    ProjectOntoAxis(axis, vertices1, min1, max1);
    ProjectOntoAxis(axis, vertices2, min2, max2);

    // Calculate the overlap between the two projections
    float overlap = 0.0f;
    if (max1 < min2 || max2 < min1) {
        // The projections do not overlap
        overlap = 0.0f;
    }
    else {
        // The projections overlap, so calculate the overlap amount
        if (min1 < min2) {
            overlap = max1 - min2;
        }
        else {
            overlap = max2 - min1;
        }
    }

    return overlap;
}

float SAT::GetOverlapCircleCircle(const ICircleCollidable& circle1, const ICircleCollidable& circle2, const Vector2& axis)
{
    return 0.0f;
}

float SAT::GetOverlapCirclePolygon(const ICircleCollidable& circle, const IPolygonCollidable& polygon, const Vector2& axis)
{
    // Project the center of the circle onto the axis
    float circleProjection = DotProduct(circle.GetPosition(), axis);

    // Project the vertices of the polygon onto the axis
    std::vector<Vector2> vertices = polygon.GetVertices();
    float min, max;
    ProjectOntoAxis(axis, vertices, min, max);

    // Calculate the overlap between the circle and polygon projections
    float overlap = 0.0f;
    if (circleProjection + circle.GetRadius() < min || circleProjection - circle.GetRadius() > max) {
        // The projections do not overlap
        overlap = 0.0f;
    }
    else {
        // The projections overlap, so calculate the overlap amount
        if (circleProjection < min) {
            overlap = circleProjection + circle.GetRadius() - min;
        }
        else if (circleProjection > max) {
            overlap = circleProjection - circle.GetRadius() - max;
        }
    }

    return overlap;
}
