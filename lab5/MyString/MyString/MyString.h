#pragma once
#include <string>
#include <sstream>
#include <memory>
#include <iterator>

class CMyString;

class CMiniStr {
public:
	CMiniStr()
	{}
	
	CMiniStr(const char * chars, size_t count):m_count(count)
	{
		if (!count)
		{
			std::invalid_argument("CMiniStr");
		}
		m_chars = std::make_unique<char[]>(count);
		memcpy(m_chars.get(), chars, count);
	}

	~CMiniStr()
	{
		m_chars.reset();
	}

	char * Get()const
	{
		return m_chars.get();
	}

	void Clear()
	{
		if (m_count > 0)
		{
			m_chars.reset();
			m_count = 0;
		}
	}

	size_t Size()
	{
		return m_count;
	}

	CMiniStr & operator=(CMiniStr&);
	char &operator[](size_t index);
private:
	size_t m_count = 0;
	std::unique_ptr<char[]> m_chars;
};


template<typename ValueType>
class StrIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
	friend class StrIterator;
public:
	StrIterator(ValueType* p);
	StrIterator(CMyString & str, size_t index);
	StrIterator(const StrIterator &it);

	bool operator!=(StrIterator const& other) const;
	bool operator==(StrIterator const& other) const; //need for BOOST_FOREACH
	typename StrIterator::reference operator*() const;
	StrIterator& operator++();
private:
	ValueType* p;
	size_t m_index;
	std::unique_ptr<CMyString> m_str;
};

template<typename ValueType>
StrIterator<ValueType>::StrIterator(CMyString & str, size_t index):m_str(std::make_unique<CMyString>(str)), m_index(index)
{
}

template<typename ValueType>
StrIterator<ValueType>::StrIterator(ValueType *p) :
	p(p)
{

}

template<typename ValueType>
StrIterator<ValueType>::StrIterator(const StrIterator& it) :
	p(it.p)
{

}

template<typename ValueType>
bool StrIterator<ValueType>::operator!=(StrIterator const& other) const
{
	return p != other.p;
}

template<typename ValueType>
bool StrIterator<ValueType>::operator==(StrIterator const& other) const
{
	return p == other.p;
}

template<typename ValueType>
typename StrIterator<ValueType>::reference StrIterator<ValueType>::operator*() const
{
	return (*m_str)[m_index];
}

template<typename ValueType>
StrIterator<ValueType> &StrIterator<ValueType>::operator++()
{
	++m_index;
	return *this;
}



class CMyString
{
public:
	typedef StrIterator<char> iterator;
	typedef StrIterator<const char> const_iterator;

	iterator begin();
	iterator end();

	//const_iterator begin() const;
	//const_iterator end() const;
	
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
