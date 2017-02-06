#include "stdafx.h"
#include <iostream>
#include "MyString.h"
#include <algorithm>
#include <boost\mpl\equal.hpp>

using namespace std;

CMyString & CMyString::operator =(const CMyString& str)
{
	if (this != &str)
	{
		m_chars = std::make_unique<char[]>(str.GetLength() + 1);
		m_length = str.GetLength();
		memcpy(m_chars.get(), str.GetStringData(),m_length);
		m_chars[m_length] = '\0';
	}
	return *this;
}

CMyString & CMyString::operator +=(const CMyString & str)
{
	std::unique_ptr<char[]> buffer;
	buffer.swap(m_chars);
	m_chars = std::make_unique<char[]>(m_length + str.m_length + 2);
	memcpy(m_chars.get(), buffer.get(), m_length + 1);
	memcpy(m_chars.get() + m_length + 1, buffer.get(), str.m_length);
	m_chars[str.m_length] = '\0';
	m_length += str.m_length + 1;
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
	return std::equal<CMyStringIterator<const char>, CMyStringIterator<const char>>(str1.begin(), str1.end(), str2.begin());
}

bool operator !=(const CMyString &str1, const CMyString &str2)
{
	return !(str1 == str2);
}

bool operator <(const CMyString &str1, const CMyString &str2)
{
	auto cmp = memcmp(str1.GetStringData(), str2.GetStringData(), std::min(str1.GetLength(), str2.GetLength()));
	return (cmp != 0 ? cmp : static_cast<int>(str1.GetLength() - str2.GetLength())) < 0;
}

bool operator >(const CMyString &str1, const CMyString &str2)
{
	auto cmp = memcmp(str1.GetStringData(), str2.GetStringData(), std::min(str1.GetLength(), str2.GetLength()));
	return (cmp != 0 ? cmp : static_cast<int>(str1.GetLength() - str2.GetLength())) > 0;
}

bool operator <=(const CMyString &str1, const CMyString &str2)
{
	return ((str1 == str2) || (str1 < str2));
}

bool operator >=(const CMyString &str1, const CMyString &str2)
{
	return ((str1 == str2) || (str1 > str2));
}

char & CMyString::operator [](size_t index)const
{
	if (index < 0 || index > m_length)
	{
		throw std::out_of_range("incorrect index");
	}
	return m_chars[index];
}

char & CMyString::operator [](size_t index)
{
	if (!(index >= 0 && index < m_length))
	{
		throw std::out_of_range("Incorrect index");
	}
	return m_chars[index];
}

ostream & operator <<(ostream & strm, CMyString const & string)
{
	return strm.write(string.GetStringData(), string.GetLength());
}

istream & operator >>(istream & strm, CMyString & string)
{
	std::string tStr;
	strm >> tStr;
	string = CMyString(tStr);
	return strm;
}