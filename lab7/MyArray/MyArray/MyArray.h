#pragma once
#include <memory>
#include <exception>
#include <iostream>
#include <iterator>
#include <initializer_list>
#include "MyIterator.h"
#include <string>


template <typename T>
class CMyArray
{
public:
	CMyArray()
	{
		m_begin = static_cast<T*>(::operator new(MINIMUM_CAPACITY));// * sizeof(T)
		m_end = m_begin;
		m_endOfCapacity = m_begin + MINIMUM_CAPACITY;
		m_size = 0;
	}

	//CMyArray(std::initializer_list<T> values)
	//{
	//	const auto size = values.size();
	//	if (size != 0)
	//	{
	//		m_begin = RawAlloc(size);
	//		try
	//		{
	//			auto begin = values.begin();
	//			for (m_end = m_begin; begin < values.end();m_end++, begin++)
	//			{
	//				new (m_end)T(*begin);
	//			}
	//			m_endOfCapacity = m_end;
	//		}
	//		catch (...)
	//		{
	//			DeleteItems(m_begin, m_end);
	//			throw;
	//		}
	//	}
	//}

	//CMyArray(const CMyArray& arr)
	//{
	//	const auto size = arr.GetSize();
	//	if (size != 0)
	//	{
	//		m_begin = RawAlloc(size);
	//		try
	//		{
	//			CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
	//			m_endOfCapacity = m_end;
	//		}
	//		catch (...)
	//		{
	//			DeleteItems(m_begin, m_end);
	//			throw;
	//		}
	//	}
	//}

	//CMyArray(const CMyArray&& arr):
	//	m_begin(arr.m_begin),
	//	m_end(arr.m_end),
	//	m_endOfCapacity(arr.m_endOfCapacity)
	//{
	//}

	//CMyArray(size_t size, T item)
	//{
	//	m_begin = RawAlloc(size);
	//	m_end = m_begin + size;
	//	try
	//	{
	//		for (m_endOfCapacity = m_begin; m_endOfCapacity < m_end; ++m_endOfCapacity)
	//		{
	//			new (m_endOfCapacity)T(item);
	//		}
	//	}
	//	catch (...)
	//	{
	//		DeleteItems(m_begin, m_end);
	//		throw;
	//	}
	//}

	void PushBack(const T & item)
	{
		if(m_endOfCapacity == m_end)
		{
			
		}
		try
		{
			new (++m_end)T(item);
			m_size++;
		}
		catch (...)
		{
			m_end--;
		}
	}

	//void Resize(size_t size)
	//{
	//	if (GetSize() < size)
	//	{
	//		if (GetCapacity() > size)
	//		{
	//			T * end = m_end + size;
	//			try
	//			{
	//				T * begin = m_end;
	//				for (++begin; begin < end; ++begin)
	//				{
	//					begin = new T;
	//				}
	//			}
	//			catch (...)
	//			{
	//				T * begin = m_end;
	//				DeleteItems(begin, end);
	//			}
	//		}
	//		else if (GetCapacity() < size)
	//		{
	//			T * begin = RawAlloc(size);
	//			T * end;
	//			CopyItems(m_begin, m_end, begin, end);
	//			DeleteItems(m_begin, m_end);
	//			m_begin = begin;
	//			m_end = end;
	//			m_endOfCapacity = begin + size;
	//		}

	//	}
	//	else if (GetSize() > size)
	//	{
	//		T * end = m_end;
	//		m_end -= size - GetSize();
	//		DeleteItems(m_end, end);
	//	}
	//}

	//T & operator [](size_t index)
	//{
	//	if (index > GetSize())
	//	{
	//		throw std::out_of_range("invalid index");
	//	}
	//	return m_begin[index];
	//}
	//const T & operator [](size_t index)const
	//{
	//	if (index > GetSize())
	//	{
	//		throw std::out_of_range("invalid index");
	//	}
	//	return m_begin[index];
	//}

	//void Clear()
	//{
	//	DeleteItems(m_begin, m_end);
	//	m_end = m_begin;
	//	m_endOfCapacity = m_begin;
	//}

	//CMyIterator<T> begin()
	//{
	//	return m_begin;
	//}
	//CMyIterator<T> end()
	//{
	//	return m_end;
	//}

	//CMyIterator<const T> begin() const
	//{
	//	return m_begin;
	//}
	//CMyIterator<const T> end() const
	//{
	//	return m_end;
	//}

	//CMyArray<T> & operator=(const CMyArray<T> & arr)
	//{
	//	const auto size = arr.GetSize();
	//	if (size != 0)
	//	{
	//		m_begin = RawAlloc(size);
	//		try
	//		{
	//			CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
	//			m_endOfCapacity = m_end;
	//		}
	//		catch (...)
	//		{
	//			DeleteItems(m_begin, m_end);
	//			throw;
	//		}
	//	}
	//	return *this;
	//}

	//CMyArray<T> & operator=(std::initializer_list<T> values)
	//{
	//	Clear();
	//	const auto size = values.size();
	//	if (size != 0)
	//	{
	//		m_begin = RawAlloc(size);
	//		try
	//		{
	//			auto begin = values.begin();
	//			for (m_end = m_begin; begin < values.end(); m_end++, begin++)
	//			{
	//				new (m_end)T(*begin);
	//			}
	//			m_endOfCapacity = m_end;
	//		}
	//		catch (...)
	//		{
	//			DeleteItems(m_begin, m_end);
	//			throw;
	//		}
	//	}
	//	return *this;
	//}

	//CMyArray<T> & operator=(const CMyArray<T> && arr)
	//{
	//	Clear();
	//	m_begin = arr.m_begin;
	//	m_end = arr.m_end;
	//	m_endOfCapacity = arr.m_endOfCapacity;
	//	return *this;
	//}

	////type cast 
	//template < typename NewTypeT >
	//operator CMyArray< NewTypeT >()
	//{
	//	CMyArray< NewTypeT > result;
	//	result.Resize<NewTypeT>(GetSize());
	//	try
	//	{
	//		auto current = m_begin;
	//		for (size_t i = 0; current < m_end; current++, i++)
	//		{
	//			result[i] = static_cast<NewTypeT>(*current);
	//		}
	//	}
	//	catch (...)
	//	{
	//		result.Clear();
	//		throw;
	//	}
	//	return result;
	//}

	//template< typename NewTypeT >
	//CMyArray(const CMyArray< NewTypeT > & values)
	//{
	//	auto m_newBegin = RawAlloc(values.GetSize());
	//	auto currentInNew = m_newBegin;
	//	try
	//	{
	//		for (size_t i = 0; i < values.GetSize(); ++i, ++currentInNew)
	//		{
	//			new (currentInNew)T(static_cast<NewTypeT>(values[i]));
	//		}
	//		Clear();
	//		m_begin = m_newBegin;
	//		m_end = currentInNew;
	//		m_endOfCapacity = currentInNew;
	//	}
	//	catch (...)
	//	{
	//		DeleteItems(m_newBegin, currentInNew);
	//		throw;
	//	}
	//}

	//template < typename NewTypeT >
	//CMyArray & operator=(const CMyArray< NewTypeT > & values)
	//{
	//	auto m_newBegin = RawAlloc(values.GetSize());
	//	auto currentInNew = m_newBegin;
	//	try
	//	{
	//		for (size_t i = 0; i < values.GetSize(); ++i, ++currentInNew)
	//		{
	//			new (currentInNew)T(static_cast<NewTypeT>(values[i]));
	//		}
	//		Clear();
	//		m_begin = m_newBegin;
	//		m_end = currentInNew;
	//		m_endOfCapacity = currentInNew;
	//	}
	//	catch (...)
	//	{
	//		DeleteItems(m_newBegin, m_newBegin);
	//		throw;
	//	}
	//	return *this;
	//}
	//

	T & GetBack()
	{
		if (GetSize() == 0u)
		{
			throw std::out_of_range("Array is empty (" + std::to_string(GetSize()) + ")");
		}
		return m_end[-1];
	}

	const T & GetBack()const
	{
		if (GetSize() == 0u)
		{
			throw std::out_of_range("Aarray is empty (" + std::to_string(GetSize()) + ")");
		}
		return m_end[-1];
	}

	size_t GetSize()const
	{
		return m_size;//m_end - m_begin;
	}

	~CMyArray()
	{
		DestroyItems(m_begin, m_end);
		RawDealloc();
	}
private:
	size_t GetCapacity()const
	{
		return m_endOfCapacity - m_begin;
	}

	void CopyItems(const T *srcBegin, T *srcEnd, T * & current)
	{
		for (; srcBegin != srcEnd; ++srcBegin, ++current)
		{
			new (current)T(*srcBegin);
		}
	}

	void DestroyItems(T * begin, T * end)
	{
		while (end != begin)
		{
			--end;
			end->~T();
		}
	}

	T * RawAlloc(size_t n)
	{
		T  * p = ::operator new(n * sizeof(T));
		return p;
	}

	void RawDealloc()
	{
		::operator delete(m_begin, sizeof(T) * (m_endOfCapacity - m_begin));
	}

	static const unsigned MINIMUM_CAPACITY = 5;
	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;

	size_t m_size = 0;
};