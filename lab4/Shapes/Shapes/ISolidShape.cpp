#include "stdafx.h"
#include "ISolidShape.h"


ISolidShape::ISolidShape()
{
}


ISolidShape::~ISolidShape()
{
}

sf::Color ISolidShape::GetColor()
{
	return m_color;
}

sf::Color ISolidShape::GetBorderColor()
{
	return m_borderColor;
}
