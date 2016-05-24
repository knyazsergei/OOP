#pragma once
#include <memory>
#include <exception>
#include <iostream>
#include <iterator>
#include <initializer_list>
#include "MyIterator.h"

template <typename T>
class CMyArray
{
public:
	CMyArray();
	CMyArray(size_t size, T item);
	CMyArray(std::initializer_list<T> values);
	CMyArray(const CMyArray<T> & arr);
	CMyArray(CMyArray<T> && arr);

	void PushBack(const T & item);
	size_t Size();
	T & operator [](size_t index);
	void Resize(size_t size, T item);
	void Clear();

	/*CMyIterator<T> begin();
	CMyIterator<T> end();

	CMyIterator<const T> begin() const;
	CMyIterator<const T> end() const;*/
private:
	size_t m_size = 0;
	std::unique_ptr<T[]> m_array;
};

template <typename T>
CMyArray<T>::CMyArray()
{

}

//template <typename T>
//CMyIterator<T> CMyArray<T>::begin()
//{
//	return CMyIterator<T>(m_array.get());
//}
//
//template <typename T>
//CMyIterator<T> CMyArray<T>::end()
//{
//	return CMyIterator<T>(m_array.get() + m_size);
//}
//
//template <typename T>
//CMyIterator<const T> CMyArray<T>::begin()const
//{
//	return CMyIterator<const T>(m_array.get());
//}
//
//template <typename T>
//CMyIterator<const T> CMyArray<T>::end()const
//{
//	return CMyIterator<const T>(m_array.get() + m_size);
//}

template <typename T>
CMyArray<T>::CMyArray(size_t size, T item)
{
	Resize(size, item);
}

template <typename T>
CMyArray<T>::CMyArray(CMyArray<T> && arr):
	m_size(arr.m_size)
{
	m_array.swap(arr.m_array);
}

template <typename T>
CMyArray<T>::CMyArray(std::initializer_list<T> values):
	m_size(values.size()),
	m_array(std::make_unique<T[]>(m_size))
{
	size_t i = 0;
	for (auto it : values)
	{
		m_array[i] = it;
		++i;
	}
}

template <typename T>
CMyArray<T>::CMyArray(const CMyArray<T> & arr):
	m_size(arr.m_size),
	m_array(std::make_unique<T[]>(m_size))
{
	memcpy(m_array.get(), arr.m_array.get(), m_size * sizeof(m_size));
}

template <typename T>
void CMyArray<T>::Clear()
{
	m_size = 0;
	m_array.reset();
}

template <typename T>
void CMyArray<T>::Resize(size_t size, T item)
{
	if (m_size > size)
	{
		m_size = size;
		return;
	}
	std::unique_ptr<T[]> buffer;
	m_array.swap(buffer);
	m_array = std::make_unique<T[]>(size);
	memcpy(m_array.get(), buffer.get(), (m_size) * sizeof(T));
	for (size_t i = m_size; i < size; ++i) 
	{
		m_array[i] = item;
	}
	m_size = size;
}

template <typename T>
T & CMyArray<T>::operator[](size_t index)
{
	if (index < 0 || index >= m_size)
	{
		throw std::out_of_range("incorrect index");
	}
	return m_array[index];
}

template <typename T>
size_t CMyArray<T>::Size()
{
	return m_size;
}

template <typename T>
void CMyArray<T>::PushBack(const T & item)
{
	++m_size;
	std::unique_ptr<T[]> buffer;
	m_array.swap(buffer);
	m_array = std::make_unique<T[]>(m_size);
	memcpy(m_array.get(), buffer.get(), (m_size - 1) * sizeof(T));
	m_array[m_size - 1] = item;
}

