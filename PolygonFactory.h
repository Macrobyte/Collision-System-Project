#pragma once
#include <vector>
#include <cmath>
#include "Vector2.h"

class PolygonFactory
{
public:
    static std::vector<Vector2> CreateSquare(float size) {
        std::vector<Vector2> vertices;
        vertices.push_back(Vector2(-size / 2, -size / 2));
        vertices.push_back(Vector2(-size / 2, size / 2));
        vertices.push_back(Vector2(size / 2, size / 2));
        vertices.push_back(Vector2(size / 2, -size / 2));
        return vertices;
    }

    static std::vector<Vector2> CreateTriangle(float size) {
        std::vector<Vector2> vertices;
        vertices.push_back(Vector2(0, -size / 2));
        vertices.push_back(Vector2(size / 2, size / 2));
        vertices.push_back(Vector2(-size / 2, size / 2));
        return vertices;
    }

    static std::vector<Vector2> CreateNonagon(float radius)
    {
        const int numSides = 9;
        const float angleStep = (2 * M_PI) / numSides;
        std::vector<Vector2> vertices;

        for (int i = 0; i < numSides; i++) {
            float angle = i * angleStep;
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            vertices.push_back(Vector2(x, y));
        }

        return vertices;
    }

    static std::vector<Vector2> CreateHexagon(float radius)
    {
        std::vector<Vector2> vertices;
        float angle = 0.0f;
        float angleStep = M_PI / 3.0f;

        for (int i = 0; i < 6; i++)
        {
            float x = radius * std::cos(angle);
            float y = radius * std::sin(angle);
            vertices.push_back(Vector2(x, y));
            angle += angleStep;
        }

        return vertices;
    }
};

