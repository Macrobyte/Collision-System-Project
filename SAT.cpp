#include "SAT.h"


bool SAT::Collides(const ICollidable& shape1, const ICollidable& shape2)
{
    std::vector<Vector2> vertices1 = shape1.GetVertices();
    std::vector<Vector2> vertices2 = shape2.GetVertices();
    std::vector<Vector2> normals1 = shape1.GetNormals();
    std::vector<Vector2> normals2 = shape2.GetNormals();

    if (dynamic_cast<const Circle*>(&shape1) || dynamic_cast<const Circle*>(&shape2))
    {
        const Circle* circle = dynamic_cast<const Circle*>(&shape1);
        const ICollidable* otherShape = &shape2;
        if (!circle) {
            circle = dynamic_cast<const Circle*>(&shape2);
            otherShape = &shape1;
        }
        if (!circle->Collides(*otherShape)) {
            return false;
        }
    }
    else
    {
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
    }

	return true;
}

void SAT::ProjectOntoAxis(const Vector2& axis, const std::vector<Vector2>& vertices, float& min, float& max)
{
    min = max = dot(axis, vertices[0]);
    for (size_t i = 1; i < vertices.size(); ++i) {
        float projection = dot(axis, vertices[i]);
        if (projection < min) {
            min = projection;
        }
        else if (projection > max) {
            max = projection;
        }
    }   
}
