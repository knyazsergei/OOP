// Shapes.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "Shapes.h"

std::unique_ptr<IShape> parseInputStr(std::string str)
{
	str.erase(std::remove_if(str.begin(), str.end(), ispunct), str.end());
	std::istringstream ss(str);
	std::string type;
	ss >> type;
	std::unique_ptr<IShape> shape;
	if (type == "rectangle")
	{
		float params[4];
		for (auto & it : params)
		{
			ss >> it;
		}
		sf::Color borderColor;
		sf::Color color;
		shape = std::make_unique<CRectangle>(std::make_unique<CDot>(params[0], params[1]), params[2], params[3], borderColor, color);
	}
	else if (type == "triangle")
	{
		float params[6];
		for (auto & it : params)
		{
			ss >> it;
		}
		sf::Color borderColor;
		sf::Color color;

		shape = std::make_unique<CTriangle>(
			std::make_unique<CDot>(params[0], params[1]),
			std::make_unique<CDot>(params[2], params[3]),
			std::make_unique<CDot>(params[4], params[5]), 
			borderColor, 
			color);
	}
	else if (type == "circle")
	{
		float params[3];
		for (auto & it : params)
		{
			ss >> it;
		}
		sf::Color borderColor;
		sf::Color color;

		shape = std::make_unique<CCircle>(
			std::make_unique<CDot>(params[0], params[1]),
			params[2],
			borderColor,
			color);
	}
	return shape;
}

int main()
{
	std::vector<std::unique_ptr<IShape>> shapes;
	parseInputStr("rectangle 20, 30, 17, 25, #ff0000, #00ff00");
    return 0;
}