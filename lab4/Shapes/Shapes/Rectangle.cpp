#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(std::unique_ptr<CDot> center, float width, float height, sf::Color borderColor, sf::Color color)
{
	m_mainCorner = std::make_shared<CDot>(*center.release());
	m_width = width;
	m_height = height;
	m_borderColor = borderColor;
	m_color = color;

	m_shape.setPosition(m_mainCorner->m_position.x, m_mainCorner->m_position.y);

	m_shape.setOutlineThickness(1);
	m_shape.setOutlineColor(borderColor);

	m_shape.setSize({ m_width, m_height });
	m_shape.setOrigin({ width * 0.5f, height * 0.5f });
	m_shape.setFillColor(color);
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
	std::ostringstream result;
	result.setf(std::ios_base::fixed, std::ios_base::floatfield);
	result << std::setprecision(2);

	result << "Rectangle <" << m_mainCorner->m_position.x << ", "
		<< m_mainCorner->m_position.y << ">, <" << m_width << ", " << m_height << "> "
		<< GetSquare() << ", P=" << GetPerimeter() << std::endl;
	
	return result.str();
}

void CRectangle::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(m_shape, state);
}
