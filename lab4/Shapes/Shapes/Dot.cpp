#include "stdafx.h"
#include "Dot.h"


CDot::CDot(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}


CDot::~CDot()
{
}

float CDot::GetSquare()
{
	return 0;
}

float CDot::GetPerimeter()
{
	return 0;
}

std::string CDot::GetStringRepresentation()
{
	return "point " + std::to_string(m_position.x) + " " + std::to_string(m_position.y);
}

sf::Color CDot::GetBorderColor()
{
	return m_borderColor;
}