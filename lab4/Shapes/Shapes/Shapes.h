#pragma once
//Interface
#include "IShape.h"
#include "ISolidShape.h"

//Basic shapes
#include "Dot.h"
#include "LineSegment.h"

#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

sf::Color colorConverter(std::string hexCode)
{
	int r = 255;
	int g = 255;
	int b = 255;
	if ((int)hexCode.size() >= 3)
	{
		if (hexCode.at(0) == '#')
		{
			hexCode.erase(0, 1);
		}
		if ((int)hexCode.size() == 3)
		{
			hexCode = hexCode.substr(0, 1) + hexCode.substr(0, 1) + hexCode.substr(1, 1) + hexCode.substr(1, 1) + hexCode.substr(2, 1) + hexCode.substr(2, 1);
		}

		if ((int)hexCode.size() == 6)
		{
			int rrrrr = 0;
			int ggggg = 0;
			int bbbbb = 0;
			std::istringstream(hexCode.substr(0, 2)) >> std::hex >> rrrrr;
			std::istringstream(hexCode.substr(2, 2)) >> std::hex >> ggggg;
			std::istringstream(hexCode.substr(4, 2)) >> std::hex >> bbbbb;
			r = rrrrr;
			g = ggggg;
			b = bbbbb;
		}
		else
		{
			//invalid hex given
			r = 0;
			g = 0;
			b = 0;
		}
	}

	sf::Color color(r, g, b);
	return color;
}