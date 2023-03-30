#pragma once
#include <vector>
#include <cmath>
#include "Vector2.h"

class PolygonFactory
{
public:
	/// <summary>
	/// Creates a Triangle with the given size
	/// </summary>
	/// <param name="size"></param>
	/// <returns></returns>
	static std::vector<Vector2> CreateTriangle(float size) {
		std::vector<Vector2> vertices;
		vertices.push_back(Vector2(0, -size / 2));
		vertices.push_back(Vector2(size / 2, size / 2));
		vertices.push_back(Vector2(-size / 2, size / 2));
		return vertices;
	}
	
    /// <summary>
	/// Creates a Square with the given size
    /// </summary>
    /// <param name="size"></param>
    /// <returns></returns>
    static std::vector<Vector2> CreateSquare(float size) {
        std::vector<Vector2> vertices;
        vertices.push_back(Vector2(-size / 2, -size / 2));
        vertices.push_back(Vector2(size / 2, -size / 2));
        vertices.push_back(Vector2(size / 2, size / 2));
        vertices.push_back(Vector2(-size / 2, size / 2));
        return vertices;
    }

	/// <summary>
	/// Creates a Pentagon with the given radius
	/// </summary>
	/// <param name="radius"></param>
	/// <returns></returns>
	static std::vector<Vector2> CreatePentagon(float radius)
	{
		std::vector<Vector2> vertices;
		float angle = 0.0f;
		float angleStep = M_PI / 2.5f;

		for (int i = 0; i < 5; i++)
		{
			float x = radius * std::cos(angle);
			float y = radius * std::sin(angle);
			vertices.push_back(Vector2(x, y));
			angle += angleStep;
		}

		return vertices;
	}
    
	/// <summary>
	/// Creates a Hexagon with the given radius
	/// </summary>
	/// <param name="radius"></param>
	/// <returns></returns>
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

	/// <summary>
	/// Creates a Heptagon with the given radius
	/// </summary>
	/// <param name="radius"></param>
	/// <returns></returns>
	static std::vector<Vector2> CreateHeptagon(float radius)
	{
		std::vector<Vector2> vertices;
		float angle = 0.0f;
		float angleStep = M_PI / 3.5f;

		for (int i = 0; i < 7; i++)
		{
			float x = radius * std::cos(angle);
			float y = radius * std::sin(angle);
			vertices.push_back(Vector2(x, y));
			angle += angleStep;
		}

		return vertices;
	}
	
	/// <summary>
	/// Creates an Octagon with the given radius
	/// </summary>
	/// <param name="radius"></param>
	/// <returns></returns>
	static std::vector<Vector2> CreateOctagon(float radius)
	{
		std::vector<Vector2> vertices;
		float angle = 0.0f;
		float angleStep = M_PI / 4.0f;

		for (int i = 0; i < 8; i++)
		{
			float x = radius * std::cos(angle);
			float y = radius * std::sin(angle);
			vertices.push_back(Vector2(x, y));
			angle += angleStep;
		}

		return vertices;
	}
	
    /// <summary>
	/// Creates a Nonagon with the given radius
    /// </summary>
    /// <param name="radius"></param>
    /// <returns></returns>
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

	/// <summary>
	/// Creates a Decagon with the given radius
	/// </summary>
	/// <param name="radius"></param>
	/// <returns></returns>
	static std::vector<Vector2> CreateDecagon(float radius)
	{
		const int numSides = 10;
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

	/// <summary>
	/// Creates a Megagon with the given radius
	/// </summary>
	/// <param name="radius"></param>
	/// <returns></returns>
	static std::vector<Vector2> CreateMegagon(float radius)
	{
		const int numSides = 1000000;
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
};

