#pragma once
#include "ISolidShape.h"
#include "Dot.h"
#define _USE_MATH_DEFINES
#include <math.h>

class CCircle :
	public ISolidShape
{
public:
	CCircle(std::unique_ptr<CDot> center, float radius, const sf::Color & borderColor, const sf::Color & color);
	~CCircle();
	virtual float GetSquare()const override;
	virtual float GetPerimeter()const override;
	virtual std::string GetStringRepresentation()const override;
	sf::Color GetColor()const override;
	sf::Color GetBorderColor()const override;
private:
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;

	std::shared_ptr<CDot> m_center;
	float m_radius;
	sf::CircleShape m_shape;
};

