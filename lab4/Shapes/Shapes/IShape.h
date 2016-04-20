#pragma once
#include <sfml/Graphics.hpp>
#include <sstream>
#include <iomanip>

class IShape:
	public sf::Drawable
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
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;// = 0;
};

