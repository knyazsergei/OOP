#pragma once
#include <sfml/Graphics.hpp>
#include <sstream>
#include <iomanip>

class IShape:
	public sf::Drawable
{
public:
	virtual ~IShape() = default;
	virtual float GetSquare()const = 0;

	virtual float GetPerimeter()const = 0;
	virtual std::string GetStringRepresentation()const = 0;
	virtual sf::Color GetBorderColor()const = 0;
protected:
	sf::Color m_borderColor;
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;
};

