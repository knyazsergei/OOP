#pragma once
#include <string>
#include <sstream>
#include <memory>
#include <iterator>
#include "MyStringIterator.h"

class CMyString
{
	typedef CMyStringIterator<char> iterator;
	typedef CMyStringIterator<const char> const_iterator;
public:
	CMyString();
	CMyString(const char *pString);
	CMyString(const char *pString, size_t length);
	CMyString(CMyString const &other);
	CMyString(CMyString &&other);
	CMyString(std::string const &stlString);
	~CMyString();

	size_t GetLength()const;
	const char* GetStringData()const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;
	void Clear();

	CMyString& operator =(const CMyString& str);
	CMyString& operator +=(const CMyString& str);
	char &operator[](size_t index) const;
	char &operator[](size_t index);

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;
private:
	size_t m_length;
	std::unique_ptr<char[]> m_chars;
};


CMyString operator +(const CMyString &str1, const CMyString &str2);
CMyString operator +(std::string const &str1, const CMyString &str2);
CMyString operator +(const char* str1, const CMyString &str2);

bool operator ==(const CMyString &str1, const CMyString &str2);
bool operator !=(const CMyString &str1, const CMyString &str2);
bool operator <(const CMyString &str1, const CMyString &str2);
bool operator >(const CMyString &str1, const CMyString &str2);
bool operator <=(const CMyString &str1, const CMyString &str2);
bool operator >=(const CMyString &str1, const CMyString &str2);

std::ostream & operator <<(std::ostream & strm, CMyString const & string);
std::istream & operator >>(std::istream & strm, CMyString & string);
