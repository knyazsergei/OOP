#pragma once
#include <iterator>
#include <type_traits>
#include <tuple>

template<typename T>
class CMyArray;

// TODO: use random access tag
template<typename T>
class CMyIterator  : public std::iterator<std::random_access_iterator_tag, T>
{
	friend class CMyArray<typename std::remove_const<T>::type>;
private:
	CMyIterator(std::tuple<T*, T**, T**> pointers);
public:
	CMyIterator(const CMyIterator &it);

	bool operator!=(CMyIterator const& other) const;
	bool operator==(CMyIterator const& other) const;
	bool operator<(CMyIterator const& other) const;
	typename CMyIterator::reference operator*() const;
	CMyIterator& operator++();//prefix
	CMyIterator& operator--();

	CMyIterator operator++(int);//postfix
	CMyIterator operator--(int);

	CMyIterator operator+=(const CMyIterator<const T> & second);
	CMyIterator operator-=(const CMyIterator<const T> & second);

	CMyIterator operator+(const CMyIterator<const T> & second) const;
	CMyIterator operator-(const CMyIterator<const T> & second) const;

	T* p;
	T** m_begin;
	T** m_end;
};

template<typename T>
CMyIterator<T> operator+(const CMyIterator<T> & first, const CMyIterator<T> & second)
{
	CMyIterator<T> result(first);
	result.p = *first.m_begin + (*first.m_end - first.p) + (*second.m_end - second.p);
	if (result.p > (*first.m_end - 1) && *first.m_end != nullptr)
	{
		throw std::logic_error("");
	}
	return result;
}

template<typename T>
CMyIterator<T> operator-(const CMyIterator<T> & first, const CMyIterator<T> & second)
{
	CMyIterator<T> result(first);
	result.p = *first.m_begin - (*first.m_end - first.p) - (*second.m_end - second.p);
	if (result.p > *first.m_begin && *first.m_begin != nullptr)
	{
		throw std::logic_error("");
	}
	return result;
}

template<typename T>
CMyIterator<T> CMyIterator<T>::operator-=(const CMyIterator<const T> & second)
{
	if (p - (typename std::remove_const<T>::type)second.p < *m_begin)
	{
		throw std::logic_error("");
	}
	p -= (typename std::remove_const<T>::type)second.p;
	return (*this);
}

template<typename T>
CMyIterator<T> CMyIterator<T>::operator+=(const CMyIterator<const T> & second)
{
	if (p + (typename std::remove_const<T>::type)second.p >= *m_end)
	{
		throw std::logic_error("");
	}
	p += (typename std::remove_const<T>::type)second.p;
	return (*this);
}

template<typename T>
bool CMyIterator<T>::operator<(CMyIterator const& other) const
{
	return addressof(*this) < addressof(other);
}

template<typename T>
CMyIterator<T> CMyIterator<T>::operator+(const CMyIterator<const T> & second) const
{
	CMyIterator result(p);
	result += second;
	if (result >= *m_end || result < *m_begin)
	{
		throw std::logic_error("");
	}
	return result;
}

template<typename T>
CMyIterator<T> CMyIterator<T>::operator-(const CMyIterator<const T> & second) const
{
	CMyIterator result(p);
	result -= second;
	if (result >= *m_end || result < *m_begin)
	{
		throw std::logic_error("");
	}
	return result;
}

//prefix
template<typename T>
CMyIterator<T> &CMyIterator<T>::operator++()
{
	if (p == (*m_end - 1) && *m_end != nullptr)
	{
		throw std::logic_error("");
	}
	++p;
	return *this;
}


template<typename T>
CMyIterator<T>& CMyIterator<T>::operator--()
{
	if (p == *m_begin)
	{
		throw std::logic_error("");
	}
	--p;
	return *this;
}

//posfix
template<typename T>
CMyIterator<T> CMyIterator<T>::operator--(int)
{
	if (p == *m_begin)
	{
		throw std::logic_error("");
	}
	CMyIterator t(*this);
	--(*this);
	return t;
}

template<typename T>
CMyIterator<T> CMyIterator<T>::operator++(int)
{
	if (p == (*m_end - 1) && *m_end != nullptr)
	{
		throw std::logic_error("");
	}
	CMyIterator t(*this);
	++(*this);
	return t;
}

template<typename T>
CMyIterator<T>::CMyIterator(std::tuple<T*,T**,T**> pointers) :
	p(std::get<0>(pointers)),
	m_begin(std::get<1>(pointers)),
	m_end(std::get<2>(pointers))
{
	if (p == *m_end && p != nullptr)
	{
		--p;
	}
}

template<typename T>
CMyIterator<T>::CMyIterator(const CMyIterator& it) :
	p(it.p)
{

}

template<typename T>
bool CMyIterator<T>::operator!=(CMyIterator const& other) const
{
	return p != other.p;
}

template<typename T>
bool CMyIterator<T>::operator==(CMyIterator const& other) const
{
	return p == other.p;
}

template<typename T>
typename CMyIterator<T>::reference CMyIterator<T>::operator*() const
{
	return *p;
}
