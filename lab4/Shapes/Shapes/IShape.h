#pragma once
#include <sfml/Graphics.hpp>

class IShape
{
public:
	IShape();
	~IShape();
	virtual float GetSquare() = 0;

	virtual float GetPerimeter() = 0;
	virtual std::string GetStringRepresentation() = 0;
	virtual sf::Color GetBorderColor() = 0;
protected:
	sf::Color m_borderColor;
};

