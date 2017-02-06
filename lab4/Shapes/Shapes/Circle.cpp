#include "stdafx.h"
#include "Circle.h"

CCircle::CCircle(std::unique_ptr<CDot> center, float radius, const sf::Color & borderColor, const sf::Color & color)
{
	m_center = std::make_shared<CDot>(*center.release());
	m_radius = radius;
	m_borderColor = borderColor;
	m_color = color;

	m_shape.setPosition(m_center->m_position);
	m_shape.setRadius(radius);
	m_shape.setOrigin({ radius, radius });

	m_shape.setOutlineThickness(1);
	m_shape.setOutlineColor(borderColor);

	m_shape.setFillColor(color);
}


CCircle::~CCircle()
{
}

float CCircle::GetSquare()const
{
	return float(M_PI * m_radius);
}

float CCircle::GetPerimeter()const
{
	return float(M_PI * m_radius * 2);
}

std::string CCircle::GetStringRepresentation()const
{
	std::ostringstream result;
	result.setf(std::ios_base::fixed, std::ios_base::floatfield);
	result << std::setprecision(2);

	result << "Circle <" << m_center->m_position.x << ", " << m_center->m_position.y << ">, R="
		<< m_radius << ", S=" << GetSquare() << ", P=" << GetPerimeter() << std::endl;

	return result.str();
}

sf::Color CCircle::GetColor() const
{
	return m_color;
}

sf::Color CCircle::GetBorderColor() const
{
	return m_borderColor;
}

void CCircle::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(m_shape, state);
}