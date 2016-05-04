#pragma once
#include "IShape.h"

class ISolidShape :
	public IShape
{
public:
	virtual sf::Color GetColor()const = 0;
	virtual sf::Color GetBorderColor()const = 0;
protected:
	sf::Color m_color;
};

