#include "stdafx.h"
#include "MyString.h"
#include <iostream>
#include <stdlib.h>
#include <list>

CMyString::CMyString()
	: CMyString("")
{
}

CMyString::CMyString(const char * pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char * pString, size_t length)
{
	m_chars = std::make_unique<char[]>(length + 1);
	memcpy(m_chars.get(), pString, length);
	m_chars[length] = '\0';
	m_length = length;
}

CMyString::CMyString(CMyString const & other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

CMyString::CMyString(CMyString && other)
	: m_length(other.m_length)
	, m_chars(other.m_chars.get())
{
}

CMyString::CMyString(std::string const & stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char * CMyString::GetStringData()const
{
	if (m_length == 0)
	{
		return "\0";
	}
	return m_chars.get();
}

CMyString CMyString::SubString(size_t start, size_t length)const
{
	if (length > 0 && start >= 0 && start + length < m_length)
	{
		return CMyString(&m_chars[start], length);
	}
	return CMyString();
}

void CMyString::Clear()
{
	m_chars.reset();
	m_length = 0;
}

CMyString::iterator CMyString::begin()
{
	return iterator(m_chars.get());
}

CMyString::iterator CMyString::end()
{
	return iterator(m_chars.get() + m_length);
}

CMyString::const_iterator CMyString::begin() const
{
	return const_iterator(m_chars.get());
}

CMyString::const_iterator CMyString::end() const
{
	return const_iterator(m_chars.get() + m_length);
}