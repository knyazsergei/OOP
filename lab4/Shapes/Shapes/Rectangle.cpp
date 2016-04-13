#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(std::unique_ptr<CDot> mainCorner, float width, float height, sf::Color borderColor, sf::Color color)
{
	m_mainCorner = std::make_shared<CDot>(*mainCorner.release());
	m_width = width;
	m_height = height;
	m_borderColor = borderColor;
	m_color = color;
}

CRectangle::~CRectangle()
{
}

float CRectangle::GetSquare()
{
	return m_height * m_width;
}

float CRectangle::GetPerimeter()
{
	return 2 * (m_width + m_height);
}

std::string CRectangle::GetStringRepresentation()
{
	return "Rectangle";
}
