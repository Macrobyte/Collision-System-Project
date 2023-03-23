#pragma once
#include "Vector2.h"
#include <SDL.h>
#include <string>

struct RGB
{
    RGB() : r(0), g(0), b(0) {}
    RGB(int r, int g, int b) : r(r), g(g), b(b) {}
    int r;
    int g;
    int b;
};

class Shape
{
public:
    Shape(std::string name, Vector2 position, Vector2 size, RGB color) : _name(name), _position(position), _size(size), _color(color) {}
    virtual ~Shape() {}

    Vector2 GetPosition() const { return _position; }
    void SetPosition(const Vector2& position) { _position = position; }

    Vector2 GetSize() const { return _size; }
    void SetSize(const Vector2& size) { _size = size; }

	RGB GetColor() const { return _color; }
	void SetColor(const RGB& color) { _color = color; }

    virtual void Draw(SDL_Renderer* renderer) = 0;
private:
    Vector2 _position;
    Vector2 _size;
	RGB _color;
	std::string _name;

    
};

