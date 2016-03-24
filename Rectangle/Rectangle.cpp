#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle()
	:m_width(0),
	m_height(0),
	m_Left(0),
	m_Top(0)
{}

CRectangle::CRectangle(int Left, int Top, int width, int height)
	:m_width(std::max(0, width)),
	m_height(std::max(0, height)),
	m_Left(Left),
	m_Top(Top)
{
	std::cout << "created" << std::endl;
}

CRectangle::~CRectangle()
{}

void CRectangle::Move(int dx, int dy)
{
	m_Left = dx;
	m_Top = dy;
	std::cout << "moved" << std::endl;
}

void CRectangle::Scale(int sx, int sy)
{
	m_width = m_width * sx * 0.001;
	m_height = m_height * sy * 0.001;
	std::cout << "scaled" << std::endl;
}

bool CRectangle::Intersect(CRectangle const & other)
{
	if (m_Left < other.m_Right && other.m_Left < m_Right && m_Top < other.m_Bottom && other.m_Top < m_Bottom)
	{
		return true;
	}
	m_width = 0;
	m_height = 0;
	return false;
}

unsigned CRectangle::GetArea() const
{
	return m_height * m_width;
}

unsigned CRectangle::GetPerimeter() const
{
	return 2 * (m_height * m_width);
}


Vector2i CRectangle::GetPosition()
{
	return { m_Left, m_Top };
}

Vector2i CRectangle::GetSize()
{
	return { m_width, m_height };
}