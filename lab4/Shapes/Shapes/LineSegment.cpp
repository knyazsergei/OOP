#include "stdafx.h"
#include "LineSegment.h"


CLineSegment::CLineSegment(std::shared_ptr<CDot> first, std::shared_ptr<CDot> second, const sf::Color & borderColor):
	m_firstDot(first), 
	m_secondDot(second)
{
	m_borderColor = borderColor;
	m_shape[0] = sf::Vertex(first->m_position);
	m_shape[1] = sf::Vertex(second->m_position);
}


CLineSegment::~CLineSegment()
{
}

float CLineSegment::GetSquare()const
{
	return 0;
}

float CLineSegment::GetPerimeter()const
{
	return sqrt(pow((m_firstDot->m_position.x - m_secondDot->m_position.x), 2)
		+ pow((m_firstDot->m_position.y - m_secondDot->m_position.y), 2));
}

std::string CLineSegment::GetStringRepresentation()const
{
	std::ostringstream result;
	result.setf(std::ios_base::fixed, std::ios_base::floatfield);
	result << std::setprecision(2);

	result << "line " << m_firstDot->m_position.x << " " << m_firstDot->m_position.y << " "
		<< m_secondDot->m_position.x << " " << m_secondDot->m_position.y << std::endl;
	return result.str();
}

sf::Color CLineSegment::GetBorderColor()const
{
	return m_borderColor;
}

void CLineSegment::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(m_shape, 2, sf::Lines, state);
	//target.draw(m_shape, state);
}