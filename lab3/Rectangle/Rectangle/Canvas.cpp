#include "stdafx.h"
#include "Canvas.h"


CCanvas::CCanvas(unsigned width, unsigned height):
	m_width(width),
	m_height(height)
{
	m_matrix = std::vector<std::vector<char>>(width);
	for (size_t i = 0; i < width; i++)
	{
		m_matrix[i].resize(height);
	}
	Clear(' ');
}

CCanvas::~CCanvas()
{
}

unsigned CCanvas::GetWidth()const
{
	return m_width;
}

unsigned CCanvas::GetHeight()const
{
	return m_height;
}

void CCanvas::Clear(char code)
{
	for (auto & x : m_matrix)
	{
		for (auto & y : x) 
		{
			y = code;
		}
	}
}

void CCanvas::SetPixel(int x, int y, char code)
{
	if ((code > 0 && code < (' ' - 1)) ||
		x < 0 || unsigned(x) >= m_width ||
		y < 0 || unsigned(y) >= m_height)
	{
		return;
	}
	m_matrix[x][y] = code;
}

char CCanvas::GetPixel(int x, int y)const
{
	if (x < 0 || unsigned(x) >= m_width ||
		y < 0 || unsigned(y) >= m_height)
	{
		return ' ';
	}
	return m_matrix[x][y];
}

void CCanvas::Write(std::ostream & ostream)const
{
	for (auto x : m_matrix)
	{
		copy(x.begin(), x.end(), std::ostream_iterator<char>(ostream, ""));
		ostream << '\n';
	}
}
