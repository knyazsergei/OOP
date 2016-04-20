#pragma once
#include "ISolidShape.h"
#include "Dot.h"
#include "LineSegment.h"

class CTriangle :
	public ISolidShape
{
public:
	CTriangle(std::unique_ptr<CDot> position, std::unique_ptr<CDot> dot1, std::unique_ptr<CDot> dot2, std::unique_ptr<CDot> dot3, sf::Color borderColor, sf::Color color);
	~CTriangle();
	virtual float GetSquare() override;
	virtual float GetPerimeter() override;
	virtual std::string GetStringRepresentation() override;
	virtual sf::Color GetBorderColor() override;
	void CTriangle::draw(sf::RenderTarget & target, sf::RenderStates state) const;
private:
	std::shared_ptr<CDot> m_firstDot;
	std::shared_ptr<CDot> m_secondDot;
	std::shared_ptr<CDot> m_thirdDot;

	std::unique_ptr<CLineSegment> m_firstLine;
	std::unique_ptr<CLineSegment> m_secondLine;
	std::unique_ptr<CLineSegment> m_thirdLine;
	
	sf::ConvexShape m_shape;
};