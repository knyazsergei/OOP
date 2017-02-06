#include "stdafx.h"
#include "Dot.h"


CDot::CDot(float x, float y)
{
	m_position = { x, y };
	m_shape.setPosition(x, y);
}


CDot::~CDot()
{
}

float CDot::GetSquare()const
{
	return 0;
}

float CDot::GetPerimeter()const
{
	return 0;
}

std::string CDot::GetStringRepresentation()const
{
	std::ostringstream result;
	result.setf(std::ios_base::fixed, std::ios_base::floatfield);
	result << std::setprecision(2);

	result << "point " << m_position.x << " " << m_position.y << std::endl;
	return result.str();
}

sf::Color CDot::GetBorderColor()const
{
	return m_borderColor;
}

void CDot::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_shape, states);
}
