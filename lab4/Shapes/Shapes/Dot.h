#pragma once
#include "IShape.h"
class CDot :
	public IShape
{
public:
	CDot(float x, float y);
	~CDot();
	virtual float GetSquare() override;
	virtual float GetPerimeter() override;
	virtual std::string GetStringRepresentation() override;
	virtual sf::Color GetBorderColor() override;
	sf::Vector2f m_position;
};

