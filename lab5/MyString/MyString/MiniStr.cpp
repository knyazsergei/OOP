#include "stdafx.h"
#include "MiniStr.h"

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
