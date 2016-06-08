#pragma once

// TODO: make random access iterator, write test cases with <algorithm> algorithms
template<typename ValueType>
class CMyStringIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
	friend class CMyString;
private:
	CMyStringIterator(ValueType* p);
public:
	CMyStringIterator(const CMyStringIterator &it);

	bool operator!=(CMyStringIterator const& other) const;
	bool operator==(CMyStringIterator const& other) const;

	CMyStringIterator& operator++();
	CMyStringIterator& operator--();
	CMyStringIterator& operator+=(size_t value);
	CMyStringIterator& operator-=(size_t value);
	ValueType operator[](size_t index)const; // TODO: remove
	typename CMyStringIterator::reference operator*() const;
private:
	ValueType* p;
};

template<typename ValueType>
ValueType CMyStringIterator<ValueType>::operator[](size_t index) const
{
	return p[index];
}

template<typename ValueType>
CMyStringIterator<ValueType>& CMyStringIterator<ValueType>::operator-=(size_t value)
{
	p -= value;
	return *this;
}

template<typename ValueType>
CMyStringIterator<ValueType>& CMyStringIterator<ValueType>::operator+=(size_t value)
{
	p += value;
	return *this;
}

template<typename ValueType>
CMyStringIterator<ValueType> &CMyStringIterator<ValueType>::operator++()
{
	++p;
	return *this;
}

template<typename ValueType>
CMyStringIterator<ValueType>& CMyStringIterator<ValueType>::operator--()
{
	--p;
	return *this;
}

template<typename ValueType>
CMyStringIterator<ValueType>::CMyStringIterator(ValueType *p) :
	p(p)
{

}

template<typename ValueType>
CMyStringIterator<ValueType>::CMyStringIterator(const CMyStringIterator& it) :
	p(it.p)
{

}

template<typename ValueType>
bool CMyStringIterator<ValueType>::operator!=(CMyStringIterator const& other) const
{
	return p != other.p;
}

template<typename ValueType>
bool CMyStringIterator<ValueType>::operator==(CMyStringIterator const& other) const
{
	return p == other.p;
}

template<typename ValueType>
typename CMyStringIterator<ValueType>::reference CMyStringIterator<ValueType>::operator*() const
{
	return *p;
}

