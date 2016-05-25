#include "stdafx.h"
#include "../MyString/MyString.h"
#include <iostream>
#include <stdlib.h>
#include <list>

CMyString::CMyString()
{
	char chars[] = "\0";
	m_chars = CMiniStr(chars, 1);
	m_length = 1;
}

CMyString::CMyString(const char * pString)
	: m_length(strlen(pString) + 1)
{
	m_chars = CMiniStr(pString, m_length);
	m_chars[m_length - 1] = '\0';
}

CMyString::CMyString(const char * pString, size_t length)
	: m_length(length + 1)
{
	m_chars = CMiniStr(pString, m_length);
	m_chars[m_length - 1] = '\0';
}

CMyString::CMyString(CMyString const & other)
	: m_length(other.m_length)
{
	m_chars = CMiniStr(other.GetStringData(), m_length);
}

CMyString::CMyString(CMyString && other)
	: m_length(other.m_length)
{
	m_chars = other.m_chars;
}

CMyString::CMyString(std::string const & stlString)
	: m_length(stlString.size() + 1)
{
	m_chars = CMiniStr(stlString.c_str(), m_length);
	m_chars[m_length - 1] = '\0';
}

CMyString::~CMyString()
{
}

size_t CMyString::GetLength() const
{
	return m_length;
}

char * CMyString::GetStringData()const
{
	if (m_flollowersCount > 0)
	{
		Glue();
	}	
	return m_chars.Get();
}

CMyString CMyString::SubString(size_t start, size_t length)const
{
	if (m_flollowersCount > 0)
	{
		Glue();
	}

	if (length > 0 && start >= 0 && length <= m_length)
	{
		return CMyString(&m_chars[start], length);
	}
	return CMyString();
}

void CMyString::Clear()
{
	m_chars.Clear();
	
	m_chars = CMiniStr("\0", 1);
	m_length = 1;

	m_flollowersCount = 0;
}

void CMyString::Glue()const
{
	if (m_flollowersCount > 0)
	{	
		char * tempStr = new char[m_length];
		//copy first str
		for (size_t i = 0; i < m_chars.Size(); ++i)
		{
			tempStr[i] = m_chars[i];
		}
		size_t lenght = m_chars.Size();
		m_chars.Clear();

		//copy others strings
		for (size_t k = 0; k < m_flollowersCount; k++)
		{
			size_t endSize = lenght + m_pFollowers[k].Size();
			for (size_t i = lenght, j = 0; i <= endSize; i++, j++)
			{
				tempStr[i] = m_pFollowers[k][j];
				lenght++;
			}
		}

		m_flollowersCount = 0;
		m_chars = CMiniStr(tempStr, m_length);
	}
}

CMiniStr::CMiniStr(const char * chars, size_t count) :m_count(count)
{
	if (!count)
	{
		std::invalid_argument("CMiniStr");
	}
	m_chars = std::make_unique<char[]>(count);
	memcpy(m_chars.get(), chars, count);
}


CMiniStr::~CMiniStr()
{
	m_chars.reset();
}

char * CMiniStr::Get()const
{
	return m_chars.get();
}

void CMiniStr::Clear()
{
	if (m_count > 0)
	{
		m_chars.reset();
		m_count = 0;
	}
}

size_t CMiniStr::Size()
{
	return m_count;
}

CMiniStr & CMiniStr::operator=(CMiniStr & str)
{
	m_chars = std::make_unique<char[]>(str.Size());
	memcpy(m_chars.get(), str.m_chars.get(), str.Size());
	m_count = str.m_count;
	return *this;
}

char & CMiniStr::operator[](size_t index)
{
	return m_chars[index];
}
