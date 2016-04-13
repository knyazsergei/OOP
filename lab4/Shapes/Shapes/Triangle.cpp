#include "stdafx.h"
#include "Triangle.h"


CTriangle::CTriangle(std::unique_ptr<CDot> dot1, std::unique_ptr<CDot> dot2, std::unique_ptr<CDot> dot3, sf::Color borderColor, sf::Color color)
{
	m_firstDot = std::make_shared<CDot>(*dot1.release());
	m_secondDot = std::make_shared<CDot>(*dot2.release());
	m_thirdDot = std::make_shared<CDot>(*dot3.release());

	//m_firstLine = std::make_unique<CLineSegment>(std::make_unique<CDot>(dot1.get()), std::make_unique<CDot>(dot2).get());

}

CTriangle::~CTriangle()
{
}

float CTriangle::GetSquare()
{
	sf::Vector2f firstVec = sf::Vector2f(m_firstDot->m_position.x, m_firstDot->m_position.y) - sf::Vector2f(m_secondDot->m_position.x, m_secondDot->m_position.y);
	sf::Vector2f secondVec = sf::Vector2f(m_firstDot->m_position.x, m_firstDot->m_position.y) - sf::Vector2f(m_thirdDot->m_position.x, m_thirdDot->m_position.y);
	float result = sqrt(pow(firstVec.x, 2) + pow(firstVec.y, 2)) *  sqrt(pow(secondVec.x, 2) + pow(secondVec.y, 2)) * 0.5f;
	return 	result;
}

float CTriangle::GetPerimeter()
{
	return m_firstLine->GetPerimeter() + m_secondDot->GetPerimeter() + m_thirdLine->GetPerimeter();
}

std::string CTriangle::GetStringRepresentation()
{
	return "Triangle";
}

sf::Color CTriangle::GetBorderColor()
{
	return m_borderColor;
}
