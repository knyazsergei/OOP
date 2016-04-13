#include "stdafx.h"
#include "Circle.h"


CCircle::CCircle(std::unique_ptr<CDot> center, float radius, const sf::Color & borderColor, const sf::Color & color)
{
	m_center = std::make_shared<CDot>(*center.release());
	m_radius = radius;
	m_borderColor = borderColor;
	m_color = color;
}


CCircle::~CCircle()
{
}

float CCircle::GetSquare()
{
	return M_PI * m_radius;
}

float CCircle::GetPerimeter()
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::GetStringRepresentation()
{
	return "Circle";
}