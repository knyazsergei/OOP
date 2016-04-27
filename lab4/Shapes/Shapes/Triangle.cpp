#include "stdafx.h"
#include "Triangle.h"


CTriangle::CTriangle(std::unique_ptr<CDot> position, std::unique_ptr<CDot> dot1, std::unique_ptr<CDot> dot2, std::unique_ptr<CDot> dot3, sf::Color borderColor, sf::Color color)
{
	m_firstDot = std::make_shared<CDot>(*dot1.release());
	m_secondDot = std::make_shared<CDot>(*dot2.release());
	m_thirdDot = std::make_shared<CDot>(*dot3.release());

	m_firstLine = std::make_unique<CLineSegment>(m_firstDot, m_secondDot, borderColor);
	m_secondLine = std::make_unique<CLineSegment>(m_firstDot, m_thirdDot, borderColor);
	m_thirdLine = std::make_unique<CLineSegment>(m_secondDot, m_thirdDot, borderColor);

	m_shape.setPosition(position->m_position);

	m_shape.setPointCount(3);

	m_shape.setPoint(0, m_firstDot->m_position);
	m_shape.setPoint(1, m_secondDot->m_position);
	m_shape.setPoint(2, m_thirdDot->m_position);

	sf::Vector2f center;
	center.x = ((m_firstDot->m_position.x + m_secondDot->m_position.x + m_thirdDot->m_position.x) / 3);
	center.y = ((m_firstDot->m_position.y + m_secondDot->m_position.y + m_thirdDot->m_position.y) / 3);
	
	m_shape.setOrigin(center);

	m_shape.setOutlineThickness(1);
	m_shape.setOutlineColor(borderColor);

	m_shape.setFillColor(color);
}

CTriangle::~CTriangle()
{
}

float CTriangle::GetSquare()const
{
	sf::Vector2f firstVec = sf::Vector2f(m_firstDot->m_position.x, m_firstDot->m_position.y) - sf::Vector2f(m_secondDot->m_position.x, m_secondDot->m_position.y);
	sf::Vector2f secondVec = sf::Vector2f(m_firstDot->m_position.x, m_firstDot->m_position.y) - sf::Vector2f(m_thirdDot->m_position.x, m_thirdDot->m_position.y);
	float result = sqrt(pow(firstVec.x, 2) + pow(firstVec.y, 2)) *  sqrt(pow(secondVec.x, 2) + pow(secondVec.y, 2)) * 0.5f;
	return 	result;
}

float CTriangle::GetPerimeter()const
{
	return m_firstLine->GetPerimeter() + m_secondDot->GetPerimeter() + m_thirdLine->GetPerimeter();
}

std::string CTriangle::GetStringRepresentation()const
{
	std::ostringstream result;
	result.setf(std::ios_base::fixed, std::ios_base::floatfield);
	result << std::setprecision(2);

	result << "Triangle <" << m_firstDot->m_position.x << ", " << m_firstDot->m_position.y << "> "
		<< m_secondDot->m_position.x << ", " << m_secondDot->m_position.y << "> "
		<< m_thirdDot->m_position.x << ", P=" << GetPerimeter() << std::endl;
	return result.str();
}

sf::Color CTriangle::GetColor()const
{
	return m_color;
}

sf::Color CTriangle::GetBorderColor()const
{
	return m_borderColor;
}

void CTriangle::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(m_shape, state);
}