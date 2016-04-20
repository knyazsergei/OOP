#include "stdafx.h"
#include "Dot.h"


CDot::CDot(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
	m_shape.setPosition(x, y);
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
	std::ostringstream result;
	result.setf(std::ios_base::fixed, std::ios_base::floatfield);
	result << std::setprecision(2);

	result << "point " << m_position.x << " " << m_position.y << std::endl;
	return result.str();
}

sf::Color CDot::GetBorderColor()
{
	return m_borderColor;
}

void CDot::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_shape, states);
}
