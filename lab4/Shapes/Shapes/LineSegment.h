#pragma once
#include "IShape.h"
#include "Dot.h"

class CLineSegment :
	public IShape
{
public:
	CLineSegment(std::shared_ptr<CDot> first, std::shared_ptr<CDot> second, const sf::Color & borderColor);
	~CLineSegment();
	virtual float GetSquare() override;
	virtual float GetPerimeter() override;
	virtual std::string GetStringRepresentation() override;
	virtual sf::Color GetBorderColor() override;
private:
	void draw(sf::RenderTarget & target, sf::RenderStates state) const;
	std::shared_ptr<CDot> m_firstDot;
	std::shared_ptr<CDot> m_secondDot;
	sf::Vertex m_shape[2];
};

