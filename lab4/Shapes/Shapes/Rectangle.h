#pragma once
#include "ISolidShape.h"
#include "Dot.h"

class CRectangle :
	public ISolidShape
{
public:
	CRectangle(std::unique_ptr<CDot> mainCorner, float width, float height, sf::Color borderColor, sf::Color color);
	~CRectangle();
	virtual float GetSquare()const override;
	virtual float GetPerimeter()const override;
	virtual std::string GetStringRepresentation()const override;
	sf::Color GetColor()const override;
	sf::Color GetBorderColor()const override;
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	
	std::shared_ptr<CDot> m_mainCorner;
	float m_width;
	float m_height;
	sf::RectangleShape m_shape;
};

