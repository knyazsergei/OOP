// Shapes.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Shapes.h"

using vecShapes = std::vector < std::unique_ptr<IShape> >;

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
		std::string strBorderColor;
		std::string strColor;
		ss >> strBorderColor;
		ss >> strColor;
		sf::Color borderColor = colorConverter(strBorderColor);
		sf::Color color = colorConverter(strColor);
		shape = std::make_unique<CRectangle>(std::make_unique<CDot>(params[0], params[1]), params[2], params[3], borderColor, color);
	}
	else if (type == "triangle")
	{
		float params[8];
		for (auto & it : params)
		{
			ss >> it;
		}

		std::string strBorderColor;
		std::string strColor;
		ss >> strBorderColor;
		ss >> strColor;
		sf::Color borderColor = colorConverter(strBorderColor);
		sf::Color color = colorConverter(strColor);

		shape = std::make_unique<CTriangle>(
			std::make_unique<CDot>(params[0], params[1]),
			std::make_unique<CDot>(params[2], params[3]),
			std::make_unique<CDot>(params[4], params[5]),
			std::make_unique<CDot>(params[6], params[7]), 
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

		std::string strBorderColor;
		std::string strColor;
		ss >> strBorderColor;
		ss >> strColor;
		sf::Color borderColor = colorConverter(strBorderColor);
		sf::Color color = colorConverter(strColor);

		shape = std::make_unique<CCircle>(
			std::make_unique<CDot>(params[0], params[1]),
			params[2],
			borderColor,
			color);
	}
	else if (type == "line")
	{
		float params[4];
		for (auto & it : params)
		{
			ss >> it;
		}

		std::string strBorderColor;
		std::string strColor;
		ss >> strBorderColor;
		ss >> strColor;
		sf::Color borderColor = colorConverter(strBorderColor);
		sf::Color color = colorConverter(strColor);

		shape = std::make_unique<CLineSegment>(
			std::make_shared<CDot>(params[0], params[1]),
			std::make_shared<CDot>(params[2], params[3]),
			borderColor);
	}
	shape->GetStringRepresentation();
	return shape;
}

void printShapesBySort(vecShapes & shapes)
{
	std::sort(shapes.begin(), shapes.end(), [](std::unique_ptr<IShape> & first, std::unique_ptr<IShape> & second)
	{
	return first->GetSquare() < second->GetSquare();
	});

	for (const auto & shape : shapes)
	{
	std::cout << shape->GetStringRepresentation() << std::endl;
	}

	std::sort(shapes.begin(), shapes.end(), [](std::unique_ptr<IShape> & first, std::unique_ptr<IShape> & second)
	{
	return first->GetPerimeter() > second->GetPerimeter();
	});

	for (const auto & shape : shapes)
	{
	std::cout << shape->GetStringRepresentation() << " " << std::endl;
	}
}

int main(int argc, char *argv[])
{
	vecShapes shapes;
	std::string fileName;
	if (argc < 2)
	{
		std::cout << "Enter file name: ";
		std::cin >> fileName;
	}
	else
	{
		fileName = argv[1];
	}
	std::ifstream iFile(fileName);
	
	if (iFile.is_open())
	{
		std::string line;
		while (getline(iFile, line))
		{
			shapes.push_back(parseInputStr(line));
		}
	}
	else
	{
		std::cout << "File " << fileName << " not found.";
	}

	
	printShapesBySort(shapes);
	sf::RenderWindow window(sf::VideoMode(500, 500), "Shapes");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		for (const auto & shape : shapes)
		{
			window.draw(*shape);
		}
		
		window.display();
	}
	
	return EXIT_SUCCESS;
}