#pragma once
#include <algorithm>
#include <iostream>

struct Vector2i
{
	int x;
	int y;
};

class CRectangle
{
public:
	CRectangle();
	CRectangle(int Left, int Top, int width, int height);
	~CRectangle();
	void Move(int dx, int dy);
	void Scale(int sx, int sy);
	bool Intersect(CRectangle const& other);
	unsigned GetArea() const;
	unsigned GetPerimeter() const;
	Vector2i GetPosition();
	Vector2i GetSize();
private:
	int m_width = 0;
	int m_height = 0;
	int m_Left;
	int m_Top;
	int m_Right;
	int m_Bottom;
	int m_Area;
	int m_Perimeter;
};

