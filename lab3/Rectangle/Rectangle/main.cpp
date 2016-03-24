// Rectangle.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <boost/regex.hpp>
#include "Rectangle.h"
#include "Canvas.h"

using namespace std;
typedef vector<CRectangle> Rectangles;

void FillRectangle(CRectangle & rect, char code, CCanvas & canvas)
{
	for (int x = rect.GetPosition().x; x < rect.GetPosition().x + rect.GetSize().x; ++x)
	{
		for (int y = rect.GetPosition().y; y < rect.GetPosition().y + rect.GetSize().y; ++y)
		{
			canvas.SetPixel(x, y, code);
		}
	}
}

vector<string> getArgs(const string & str)
{
	vector<string> result;
	string line = "";
	for (auto ch : str)
	{
		if (ch == ' ')
		{
			result.push_back(line);
			line = "";
		}
		line += ch;
	}
	result.push_back(line);
	return result;
}

void perform(const string & line, Rectangles & rectangles)
{
	vector<string> args;
	args = getArgs(line);
	if (args[0] == "Rectangle")
	{
		rectangles.push_back(
			CRectangle(atoi(args[1].c_str()),
				atoi(args[2].c_str()),
				atoi(args[3].c_str()),
				atoi(args[4].c_str())
				));
	}
	else if (args[0] == "Move")
	{
		(--rectangles.end())->Move(atoi(args[1].c_str()), atoi(args[2].c_str()));
	}
	else if (args[0] == "Scale")
	{
		(--rectangles.end())->Scale(atoi(args[1].c_str()), atoi(args[2].c_str()));
	}
}

int main(int argc, char *argv[])
{
	/*
	if (argc != 3)
	{
		EXIT_FAILURE;
	}
	*/
	Rectangles rectangles;

	ifstream FirstFile("input1.txt");
	if (FirstFile.is_open())
	{
		string line;
		while (getline(FirstFile, line)) {
			perform(line, rectangles);
		}
	}
	ifstream SecondFile("input2.txt");
	if (SecondFile.is_open())
	{
		string line;
		while (getline(SecondFile, line)) {
			perform(line, rectangles);
		}
	}
	size_t i = 0;
	cout << endl;
	for (auto rectangle : rectangles)
	{
		cout << "Rectangle " << i << ':' << endl;
		cout << "\t" << "Left top :" << '(' << rectangle.GetPosition().x << ';' << rectangle.GetPosition().y << ')' << endl;
		cout << "\t" << "Size :" << '(' << rectangle.GetSize().x << "*" << rectangle.GetSize().y << ')' << endl; 
		cout << "\t" << "Right bottom :" << '(' << rectangle.GetPosition().x + rectangle.GetSize().x << ';' << rectangle.GetPosition().y + rectangle.GetSize().y << ')' << endl;
		cout << "\t" << "Area :" << rectangle.GetArea() << endl;
		cout << "\t" << "Perimeter :" << rectangle.GetPerimeter() << endl;
	}

	CCanvas canvas(20, 20);
	FillRectangle(rectangles[0], '+', canvas);
	FillRectangle(rectangles[1], '-', canvas);

	canvas.Write(cout);
	return 0;
}

