#pragma once
#include <iterator>
#include <type_traits>

template<typename T>
class CMyArray;

// TODO: use random access tag
template<typename T>
class CMyIterator  : public std::iterator<std::random_access_iterator_tag, T>
{
	friend class CMyArray<typename std::remove_const<T>::type>;
private:
	CMyIterator(T* p);
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

	// TODO: add operator+ (think twice about offset signness and type size)
	// TODO: add operator- (think twice about offset signness and type size)
	
	T* p;
};

template<typename T>
CMyIterator<T> operator+(const CMyIterator<T> & first, const CMyIterator<T> & second)
{
	CMyIterator<T> result(first);
	result.p = first.p + second.p * sizeof(T);
	return result;
}

template<typename T>
CMyIterator<T> operator-(const CMyIterator<T> & first, const CMyIterator<T> & second)
{
	CMyIterator<T> result(first);
	result.p = first.p - second.p * sizeof(T);
	return result;
}

template<typename T>
CMyIterator<T> CMyIterator<T>::operator-=(const CMyIterator<const T> & second)
{
	p -= (typename std::remove_const<T>::type)second.p;
	return (*this);
}

template<typename T>
CMyIterator<T> CMyIterator<T>::operator+=(const CMyIterator<const T> & second)
{
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
	return result;
}

template<typename T>
CMyIterator<T> CMyIterator<T>::operator-(const CMyIterator<const T> & second) const
{
	CMyIterator result(p);
	result -= second;
	return result;
}

//prefix
template<typename T>
CMyIterator<T> &CMyIterator<T>::operator++()
{
	++p;
	return *this;
}


template<typename T>
CMyIterator<T>& CMyIterator<T>::operator--()
{
	--p;
	return *this;
}

//posfix
template<typename T>
CMyIterator<T> CMyIterator<T>::operator--(int)
{
	CMyIterator t(*this);
	--(*this);
	return t;
}

template<typename T>
CMyIterator<T> CMyIterator<T>::operator++(int)
{
	CMyIterator t(*this);
	++(*this);
	return t;
}

template<typename T>
CMyIterator<T>::CMyIterator(T *p) :
	p(p)
{

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
