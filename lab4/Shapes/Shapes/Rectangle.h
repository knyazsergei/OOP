#pragma once
#include "ISolidShape.h"
#include "Dot.h"

class CRectangle :
	public ISolidShape
{
public:
	CRectangle(std::unique_ptr<CDot> mainCorner, float width, float height, sf::Color borderColor, sf::Color color);
	~CRectangle();
	virtual float GetSquare() override;
	virtual float GetPerimeter() override;
	virtual std::string GetStringRepresentation() override;
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	
	std::shared_ptr<CDot> m_mainCorner;
	float m_width;
	float m_height;
	sf::RectangleShape m_shape;
};

