#pragma once
#include <memory>
#include <exception>
#include <iostream>
#include <iterator>
#include <initializer_list>
#include <string>
#include "MyIterator.h"


template <typename T>
class CMyArray
{
public:
	CMyArray()
	{
		ResizeCapcity();
		m_size = 0;
	}

	CMyArray(std::initializer_list<T> values)
	{
		const auto size = values.size();
		if (size != 0)
		{
			auto begin = RawAlloc(size);
			auto end = begin;
			try
			{
				auto v_begin = values.begin();
				for (; v_begin < values.end(); end++, v_begin++)
				{
					new (end)T(*v_begin);
				}
				m_begin = begin;
				m_end = end;
				m_endOfCapacity = m_begin + size - 1;;
			}
			catch (...)
			{
				DestroyItems(begin, end);
				throw;
			}
		}
	}

	CMyArray(const CMyArray& arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			m_end = m_begin;
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DestroyItems(m_begin, m_end);
				throw;
			}
		}
	}

	CMyArray(const CMyArray&& arr):
		m_begin(arr.m_begin),
		m_end(arr.m_end),
		m_endOfCapacity(arr.m_endOfCapacity)
	{
	}

	CMyArray(size_t size, T item)
	{
		Resize(size);
		auto end = m_begin;
		try
		{
			
			for (; end != m_end; ++end)
			{
				new (end)T(item);
			}
		}
		catch (...)
		{
			DestroyItems(m_begin, end);
			m_end = m_begin;
			throw;
		}
	}

	void PushBack(const T & item)
	{
		if(m_begin == m_end && GetCapacity() <= MINIMUM_CAPACITY)
		{
			ResizeCapcity(GetCapacity() + 1);
		}
		try
		{
			new (m_end++)T(item);
		}
		catch (...)
		{
			m_end--;
			throw;
		}
	}

	void Resize(size_t size)
	{
		auto end = m_end;
		if (GetSize() < size)
		{
			if (GetCapacity() > size)
			{
				m_end += size - GetSize();
			}
			else if (GetCapacity() < size)
			{
				ResizeCapcity(size);
			}
			try
			{
				end = m_end;
				m_end = m_begin + size;
				for (; end != m_end; end++)
				{
					new (end)T();
				}
			}
			catch(...)
			{
				throw;
			}
		}
		else if (GetSize() > size)
		{
			m_end -= GetSize() - size;
			DestroyItems(m_end, end);
		}
	}

	T & operator [](size_t index)
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("invalid index");
		}
		return m_begin[index];
	}
	const T & operator [](size_t index)const
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("invalid index");
		}
		return m_begin[index];
	}

	void Clear()
	{
		DestroyItems(m_begin, m_end);
		ResizeCapcity();
		m_end = m_begin;
	}


	//Работа с итератором 
	CMyIterator<T> begin()
	{
		return m_begin;
	}
	CMyIterator<T> end()
	{
		return m_end;
	}

	CMyIterator<const T> begin() const
	{
		return m_begin;
	}
	CMyIterator<const T> end() const
	{
		return m_end;
	}

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
		return m_end - m_begin;
	}

	~CMyArray()
	{
		DestroyItems(m_begin, m_end);
		RawDealloc();
	}
private:
	void ResizeCapcity(size_t size = MINIMUM_CAPACITY)
	{
		if (GetCapacity() < size)
		{
			T * begin = RawAlloc(size);
			T * end = begin;
			try {
				//Копируем старые элементы
				CopyItems(m_begin, m_end, end);
				//удаляем старые элементы
				DestroyItems(m_begin, m_end);
				RawDealloc();
			}
			catch (...)
			{
				throw;
			}
			//Присваиваем новые значения

			m_begin = begin;
			m_end = end;
			m_endOfCapacity = m_begin + size;
		}
	}

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
		n++;
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	void RawDealloc()
	{
		::operator delete((void*)m_begin);// , sizeof(T) * GetCapacity());
	}

	static const unsigned MINIMUM_CAPACITY = 5;
	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;

	size_t m_size = 0;
};