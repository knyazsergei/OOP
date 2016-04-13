#pragma once
#include "IShape.h"

class ISolidShape :
	public IShape
{
public:
	ISolidShape();
	~ISolidShape();
	sf::Color GetColor();
	virtual sf::Color GetBorderColor() override;
protected:
	sf::Color m_color;
};

