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
	virtual float GetSquare() override;
	virtual float GetPerimeter() override;
	virtual std::string GetStringRepresentation() override;
private:
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;

	std::shared_ptr<CDot> m_center;
	float m_radius;
	sf::CircleShape m_shape;
};

