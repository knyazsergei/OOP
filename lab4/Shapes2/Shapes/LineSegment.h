#pragma once
#include "IShape.h"
#include "Dot.h"

class CLineSegment :
	public IShape
{
public:
	CLineSegment(std::shared_ptr<CDot> first, std::shared_ptr<CDot> second, const sf::Color & borderColor);
	~CLineSegment();
	virtual float GetSquare()const override;
	virtual float GetPerimeter()const override;
	virtual std::string GetStringRepresentation()const override;
	virtual sf::Color GetBorderColor()const override;
private:
	void draw(sf::RenderTarget & target, sf::RenderStates state) const;
	std::shared_ptr<CDot> m_firstDot;
	std::shared_ptr<CDot> m_secondDot;
	sf::Vertex m_shape[2];
};

