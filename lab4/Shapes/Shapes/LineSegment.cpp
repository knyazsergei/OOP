#include "stdafx.h"
#include "LineSegment.h"


CLineSegment::CLineSegment(std::shared_ptr<CDot> first, std::shared_ptr<CDot> second):
	m_firstDot(first), 
	m_secondDot(second)
{
}


CLineSegment::~CLineSegment()
{
}

float CLineSegment::GetSquare()
{
	return 0;
}

float CLineSegment::GetPerimeter()
{
	return sqrt(pow((m_firstDot->m_position.x - m_secondDot->m_position.x), 2) 
				+ pow((m_firstDot->m_position.y - m_secondDot->m_position.y), 2));
}

std::string CLineSegment::GetStringRepresentation()
{
	return "line "
		+ std::to_string(m_firstDot->m_position.x)
		+ " "
		+ std::to_string(m_firstDot->m_position.y)
		+ "  "
		+ std::to_string(m_secondDot->m_position.x)
		+ " "
		+ std::to_string(m_secondDot->m_position.y);
}

sf::Color CLineSegment::GetBorderColor()
{
	return m_borderColor;
}
