#pragma once
#include "IShape.h"
class CDot :
	public IShape
{
public:
	CDot(float x, float y);
	~CDot();
	virtual float GetSquare()const override;
	virtual float GetPerimeter()const override;
	virtual std::string GetStringRepresentation()const override;
	virtual sf::Color GetBorderColor()const override;
	sf::Vector2f m_position;
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	sf::RectangleShape m_shape = sf::RectangleShape({ 1,1 });
};

