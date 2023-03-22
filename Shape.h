#pragma once
#include "Vector2.h"
#include <SDL.h>

class Shape
{
public:
    Shape(Vector2 position, Vector2 size) : _position(position), _size(size) {}
    virtual ~Shape() {}

    Vector2 GetPosition() const { return _position; }
    void SetPosition(const Vector2& position) { _position = position; }

    Vector2 GetSize() const { return _size; }
    void SetSize(const Vector2& size) { _size = size; }

    virtual void Draw(SDL_Renderer* renderer, SDL_Color color) = 0;
private:
    Vector2 _position;
    Vector2 _size;
};

