#pragma once
#include "Shape.h"

class Square : public Shape
{
public:
	Square(Vector2 position, Vector2 size, RGB color) : Shape("Square", position, size, color) {}
	~Square(){}

	void Draw(SDL_Renderer* renderer) override;
};

