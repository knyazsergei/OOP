#include "stdafx.h"
#include "../MyString/MyString.h"
#include <iostream>

using namespace std;

CMyString & CMyString::operator =(const CMyString& str)
{
	if (this != &str)
	{
		m_length = str.GetLength() + 1;
		m_chars.Clear();
		m_chars = CMiniStr( str.GetStringData(), m_length );
		m_flollowersCount = 0;
	}

	return *this;
}

CMyString & CMyString::operator +=(const CMyString & str)
{
	m_length += str.m_length;
	if (m_flollowersCount < MAX_FOLLOWERS_COUNT)
	{
		m_pFollowers[m_flollowersCount] = CMiniStr(str.GetStringData(),str.GetLength());
		++m_flollowersCount;
	}
	else
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
		
		size_t j = 0;
		for (size_t i = lenght; i < m_length; ++i)
		{
			tempStr[i] = m_chars[j];
			j++;
		}

		m_chars = CMiniStr(tempStr, m_length);
	}
	return *this;
}

CMyString operator +(CMyString const &str1, CMyString const &str2)
{
	return (CMyString(str1) += str2);
}

CMyString operator +(std::string const &str1, CMyString const &str2)
{
	return (CMyString(str1.c_str()) += str2);
}

CMyString operator +(const char* str1, CMyString const &str2)
{
	return (CMyString(str1) += str2);
}

bool operator ==(const CMyString &str1, const CMyString &str2)
{
	if (str1.GetLength() != str2.GetLength())
	{
		return false;
	}
	for (size_t i = 0; i < str1.GetLength(); ++i)
	{
		if (str1[i] != str2[i])
		{
			return false;
		}
	}
	return true;
}

bool operator !=(const CMyString &str1, const CMyString &str2)
{
	return !(str1 == str2);
}

bool operator <(const CMyString &str1, const CMyString &str2)
{
	return (memcmp(str1.GetStringData()
		, str2.GetStringData()
		, static_cast<size_t>(fmaxl(str1.GetLength(), str2.GetLength()))) == -1);
}

bool operator >(const CMyString &str1, const CMyString &str2)
{
	return (memcmp(str1.GetStringData()
		, str2.GetStringData()
		, static_cast<size_t>(fmaxl(str1.GetLength(), str2.GetLength()))) == 1);
}

bool operator <=(const CMyString &str1, const CMyString &str2)
{
	return ((str1 == str2) || (str1 < str2));
}

bool operator >=(const CMyString &str1, const CMyString &str2)
{
	return ((str1 == str2) || (str1 > str2));
}

const char & CMyString::operator [](size_t index)const
{
	char empty = '\0';
	if (m_flollowersCount > 0)
	{
		Glue();
	}
	return (index >= 0 && index < m_length) ? m_chars[index] : empty;
}

char & CMyString::operator [](size_t index)
{
	if (!(index >= 0 && index < m_length))
	{
		throw std::invalid_argument("Incorrect index");
	}
	if (m_flollowersCount > 0)
	{
		Glue();
	}
	return m_chars[index];
}

ostream & operator <<(ostream & strm, CMyString const & string)
{
	strm << string.GetStringData();
	return strm;
}

istream & operator >>(istream & strm, CMyString & string)
{
	char tmp[2048];
	strm.getline(tmp, sizeof(tmp));
	string = CMyString(tmp);

	return strm;
}