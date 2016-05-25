#pragma once
#include <string>
#include <sstream>
#include <memory>
#include <iterator>

class CMiniStr
{
public:
	CMiniStr()
	{}

	CMiniStr(const char * chars, size_t count);

	~CMiniStr();

	char * Get()const;

	void Clear();

	size_t Size();

	CMiniStr & operator=(CMiniStr&);
	char &operator[](size_t index);
private:
	size_t m_count = 0;
	std::unique_ptr<char[]> m_chars;
};


class CMyString
{
public:
	
	CMyString();
	CMyString(const char *pString);
	CMyString(const char *pString, size_t length);
	CMyString(CMyString const &other);
	CMyString(CMyString &&other);
	CMyString(std::string const &stlString);
	~CMyString();

	size_t GetLength()const;
	char* GetStringData()const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;
	void Clear();

	CMyString& operator =(const CMyString& str);
	CMyString& operator +=(const CMyString& str);
	const char &operator[](size_t index) const;
	char &operator[](size_t index);
private:
	void Glue()const;
	size_t m_length;
	mutable CMiniStr m_chars;

	const size_t MAX_FOLLOWERS_COUNT = 10;
	mutable CMiniStr m_pFollowers[10];
	mutable size_t m_flollowersCount = 0;
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
