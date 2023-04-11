#include "SAT.h"

/// <summary>
/// The function takes in two objects that implement the IPolygonCollidable interface, which provides a method to retrieve the vertices of the polygon. 
/// The function then calculates all the unique axes of both polygons by performing cross products between the edges of each polygon.
/// </summary>
/// <param name="polygon1"></param>
/// <param name="polygon2"></param>
/// <returns>True or False depending on if the polygons collided</returns>
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

/// <summary>
/// This function checks for collision between two circles by comparing the distance between their centers to the sum of their radii. 
/// If the distance is less than the sum of the radii, then the circles are overlapping and there is a collision.
/// </summary>
/// <param name="circle1"></param>
/// <param name="circle2"></param>
/// <returns></returns>
bool SAT::CircleCircleCollision(ICircleCollidable& circle1, ICircleCollidable& circle2)
{
    float distance = (circle1.GetPosition() - circle2.GetPosition()).magnitude();
    float radiusSum = circle1.GetRadius() + circle2.GetRadius();

    return distance < radiusSum;
}

/// <summary>
/// This function checks for collision between a circle and a polygon by projecting the circle onto each axis of the polygon and checking for overlap.
/// </summary>
/// <param name="polygon"></param>
/// <param name="circle"></param>
/// <returns></returns>
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

/// <summary>
/// This function calculates the collision normal between two polygons using the Separating Axis Theorem (SAT) algorithm. 
/// The collision normal is the direction in which the polygons are separating, and is used to calculate the collision response (e.g. bouncing off each other).
/// </summary>
/// <param name="polygon1"></param>
/// <param name="polygon2"></param>
/// <returns></returns>
Vector2 SAT::GetCollisionNormalPolygon(const IPolygonCollidable& polygon1, const IPolygonCollidable& polygon2)
{
 
    std::vector<Vector2> vertices1 = polygon1.GetVertices();
    std::vector<Vector2> vertices2 = polygon2.GetVertices();

    // Combine the axes of both polygons
    std::vector<Vector2> axes;
    GetUniqueAxes(vertices1, axes);
    GetUniqueAxes(vertices2, axes);

    // Initialize minimum overlap and collision normal
    float minOverlap = std::numeric_limits<float>::max();
    Vector2 collisionNormal;

    // Project vertices of both polygons onto each axis
    for (size_t i = 0; i < axes.size(); i++)
    {
        Vector2 axis = axes[i];

        // Project vertices of polygon 1 onto the current axis
        float min1 = DotProduct(vertices1[0], axis);
        float max1 = min1;

        for (size_t j = 1; j < vertices1.size(); j++)
        {
            float projection = DotProduct(vertices1[j], axis);
            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        // Project vertices of polygon 2 onto the current axis
        float min2 = DotProduct(vertices2[0], axis);
        float max2 = min2;

        for (size_t j = 1; j < vertices2.size(); j++)
        {
            float projection = DotProduct(vertices2[j], axis);
            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        // Check for overlap on the current axis
        float overlap = std::max(0.0f, std::min(max1, max2) - std::max(min1, min2));

        // If there is no overlap on the current axis, the polygons do not collide
        if (overlap == 0.0f)
        {
            return Vector2(0, 0);
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

/// <summary>
///  This function calculates the collision normal between two circles using the Separating Axis Theorem (SAT) algorithm.
///  The collision normal is the direction in which the circles are separating, and is used to calculate the collision response (e.g. bouncing off each other).
/// </summary>
/// <param name="circle1"></param>
/// <param name="circle2"></param>
/// <returns></returns>
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

/// <summary>
/// This function calculates the collision normal between a circle and a polygon using the Separating Axis Theorem (SAT) algorithm.
/// The collision normal is the direction in which the circle and polygon are separating, and is used to calculate the collision response.
/// NOT CURRENTLY WORKING!
/// </summary>
/// <param name="circle"></param>
/// <param name="polygon"></param>
/// <returns></returns>
Vector2 SAT::GetCollisionNormalCirclePolygon(const ICircleCollidable& circle, const IPolygonCollidable& polygon)
{
    Vector2 circlePosition = circle.GetPosition();
    std::vector<Vector2> polygonVertices = polygon.GetVertices();

    // Calculate the closest vertex of the polygon to the circle
    float minDistance = FLT_MAX;
    Vector2 closestVertex;
    for (const auto& vertex : polygonVertices) {
        float distance = (vertex - circlePosition).magnitude();
        if (distance < minDistance) {
            minDistance = distance;
            closestVertex = vertex;
        }
    }

    // Calculate the collision normal from the circle's center to the closest vertex
    Vector2 collisionNormal = (circlePosition - closestVertex).normalize();

    return collisionNormal;
}

/// <summary>
/// This function calculates the overlap between two polygons along a given axis.
/// </summary>
/// <param name="polygon1"></param>
/// <param name="polygon2"></param>
/// <param name="axis"></param>
/// <returns></returns>
float SAT::GetOverlapPolygon(const IPolygonCollidable& polygon1, const IPolygonCollidable& polygon2, const Vector2& axis)
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

/// <summary>
/// This function calculates the overlap between a circle and a polygon projected onto a given axis. 
/// It takes in two arguments - an object that implements the ICircleCollidable interface and an object that implements the IPolygonCollidable interface, as well as a Vector2 axis to project onto. 
/// The function returns a float representing the overlap amount between the circle and polygon projections.
/// NOT CURRENTLY WORKING!
/// </summary>
/// <param name="circle"></param>
/// <param name="polygon"></param>
/// <param name="axis"></param>
/// <returns></returns>
float SAT::GetOverlapCirclePolygon(const ICircleCollidable& circle, const IPolygonCollidable& polygon, const Vector2& axis)
{
    float circleRadius = circle.GetRadius();
    Vector2 circlePosition = circle.GetPosition();
    std::vector<Vector2> polygonVertices = polygon.GetVertices();

    // Ensure that the polygon has at least three vertices
    if (polygonVertices.size() < 3) {
        return 0.0f;
    }

    // Project the circle's center and vertices onto the axis
    float circleProjection = DotProduct(circlePosition, axis);
    float min1 = circleProjection - circleRadius;
    float max1 = circleProjection + circleRadius;
    float min2, max2;
    ProjectOntoAxis(axis, polygonVertices, min2, max2);

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

/// <summary>
/// This function calculates unique axes from a list of vertices of a convex polygon. 
/// It takes in two parameters: a vector of vertices and a reference to a vector of axes. 
/// The function iterates over each vertex of the polygon, calculates the normal vector of the edge between the current vertex and the next vertex, and checks if the normal is unique by comparing it to the existing axes in the axes vector. 
/// If the normal is unique, it is added to the axes vector. At the end of the function, the axes vector contains all the unique axes of the polygon.
/// </summary>
/// <param name="vertices"></param>
/// <param name="axes"></param>
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

/// <summary>
/// This function projects a set of vertices onto a given axis and returns the minimum and maximum values of the resulting projections.
/// </summary>
/// <param name="axis"></param>
/// <param name="vertices"></param>
/// <param name="min"></param>
/// <param name="max"></param>
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