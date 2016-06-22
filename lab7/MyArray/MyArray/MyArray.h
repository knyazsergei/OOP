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
	CMyArray() = default;

	CMyArray(std::initializer_list<T> values)
	{
		const auto size = values.size();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				m_end = m_begin;
				auto begin = values.begin();
				for (; begin < values.end();m_end++, begin++)
				{
					new (m_end)T(*begin);
				}
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
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
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
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
			
		m_begin = RawAlloc(size);
		m_end = m_begin;
		m_end += sizeof(T) * size;
		try
		{
			for (m_endOfCapacity = m_begin; m_endOfCapacity < m_end; ++m_endOfCapacity)
			{
				// Construct "T" at "dstEnd" as a copy of "*begin"
				new (m_endOfCapacity)T(item);
			}
		}
		catch (...)
		{
			DeleteItems(m_begin, m_end);
			throw;
		}
	}

	void PushBack(const T & item)
	{
		if(m_endOfCapacity == m_end)
		{
			Resize(GetCapacity() + 1);
		}
		
		try
		{
			new (++m_endOfCapacity)T(item);
		}
		catch (...)
		{
			free(m_endOfCapacity--);
		}
	}

	void Resize(size_t size)
	{
		if (GetSize() < size)
		{
			if (GetCapacity() > size)
			{
				T * end = m_end + size * T;
				try
				{
					T * begin = m_end;
					for (++begin; begin < end; ++begin)
					{
						begin = new T;
					}
				}
				catch (...)
				{
					T * begin = m_end;
					DeleteItems(begin, end);
				}
				
			}
			else if (GetCapacity() < size)
			{
				T * begin = RawAlloc(size);
				T * end;
				CopyItems(m_begin, m_end, begin, end);
				DeleteItems(m_begin, m_end);
				m_begin = begin;
				m_endOfCapacity = end;
				m_end = end;
			}

		}
		else if (GetSize() > size)
		{
			T * end = m_end;
			m_end -= size - GetSize();
			DeleteItems(m_end, end);
		}
	}

	T & operator [](size_t index)
	{
		if (index > GetSize())
		{
			throw std::out_of_range();
		}
		return m_begin[index];
	}
	const T & operator [](size_t index)const
	{
		if (index > GetSize())
		{
			throw std::out_of_range();
		}
		return m_begin[index]
	}

	void Clear()
	{
		DeleteItems(m_begin, m_end);
		m_end = m_begin
	}

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

	CMyArray<T> & operator=(const CMyArray<T> & arr)
	{
		CMyArray(arr);
	}
	CMyArray<T> & operator=(std::initializer_list<T> values)
	{
		CMyArray(values);
	}
	CMyArray<T> & operator=(const CMyArray<T> && arr)
	{
		Clear();
		CMyArray(arr);
	}
	/*CMyArray(const CMyArray<T> & arr);*
	CMyArray(size_t size, T item);*
	CMyArray(std::initializer_list<T> values);*
	CMyArray(CMyArray<T> && arr);*

	void PushBack(const T & item);
	size_t Size()const;
	T & operator [](size_t index);
	const T & operator [](size_t index)const;
	void Resize(size_t size);
	void Resize(size_t size, const T & item);
	void Clear();

	CMyIterator<T> begin();
	CMyIterator<T> end();

	CMyIterator<const T> begin() const;
	CMyIterator<const T> end() const;

	CMyArray<T> & operator=(const CMyArray<T> & arr);
	CMyArray<T> & operator=(std::initializer_list<T> values);
*/

	T & GetBack()
	{
		if (GetSize() != 0u)
		{
			throw std::out_of_range("The array is empty");
		}
		return m_end[-1];
	}

	const T & GetBack()const
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	size_t GetSize()const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity()const
	{
		return m_endOfCapacity - m_begin;
	}
	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}
private:

	static void DeleteItems(T *begin, T *end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T *srcBegin, T *srcEnd, T * const dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd)T(*srcBegin);
		}
	}

	static void DestroyItems(T *from, T *to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
			to->~T();
		}
	}

	static T *RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T *p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T *p)
	{
		free(p);
	}

	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;
};




//
//template <typename T>
//CMyArray<T> & CMyArray<T>::operator=(std::initializer_list<T> values)
//{
//	m_arr = std::make_unique<T>(values.Size());
//	size_t i = 0;
//	for (auto it : values)
//	{
//		m_array[i] = it;
//		++i;
//	}
//	return *this;
//}
//
//template <typename T>
//CMyArray<T> & CMyArray<T>::operator=(const CMyArray<T> & arr)
//{
//	m_arr = std::make_unique<T>(arr.Size());
//	memcpy(m_array.get(), arr.m_array.get(), m_size * sizeof(m_size));
//	return *this;
//}
//
//template <typename T>
//CMyArray<T>::CMyArray()
//{
//
//}
//
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
//
//template <typename T>
//CMyArray<T>::CMyArray(size_t size, T item)
//{
//	Resize(size, item);
//}
//
//template <typename T>
//CMyArray<T>::CMyArray(CMyArray<T> && arr):
//	m_size(arr.m_size)
//{
//	m_array.swap(arr.m_array);
//}
//
//template <typename T>
//CMyArray<T>::CMyArray(std::initializer_list<T> values):
//	m_array(std::make_unique<T[]>(m_size)),
//	m_size(values.size())
//{
//	std::copy<CMyIterator<const T>, CMyIterator<T> >(values.begin(), values.end(), begin());
//}
//
//template <typename T>
//CMyArray<T>::CMyArray(const CMyArray<T> & arr):
//	m_array(std::make_unique<T[]>(m_size)),
//	m_size(arr.m_size)
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
//	//std::copy<CMyIterator<const T>, CMyIterator<T> >(arr.begin(), arr.end(), begin());
//}
//
//template <typename T>
//void CMyArray<T>::Clear()
//{
//	m_size = 0;
//	DeleteItems(m_begin, m_endOfCapacity);
//	//m_array.reset();
//}
//
//
//template <typename T>
//void CMyArray<T>::Resize(size_t size)
//{
//	if (m_size < size)
//	{
//		throw std::invalid_argument("incorrect size");
//	}
//	std::unique_ptr<T[]> buffer;
//	m_array.swap(buffer);
//	m_array = std::make_unique<T[]>(size);
//	//std::copy<CMyIterator<const T>, CMyIterator<T> >(m_array.begin(), m_array.end(), std::begin(buffer.get()));
//	memcpy(m_array.get(), buffer.get(), (size) * sizeof(T));
//	m_size = size;
//}
//
//template <typename T>
//void CMyArray<T>::Resize(size_t size, const T & item)
//{
//	if (m_size > size)
//	{
//		Resize(size);
//		return;
//	}
//	std::unique_ptr<T[]> buffer;
//	m_array.swap(buffer);
//	m_array = std::make_unique<T[]>(size);
//	memcpy(m_array.get(), buffer.get(), (m_size) * sizeof(T));
//	for (size_t i = m_size; i < size; ++i) 
//	{
//		m_array[i] = item;
//	}
//	m_size = size;
//}
//
//template <typename T>
//T & CMyArray<T>::operator[](size_t index)
//{
//	if (index >= m_size)
//	{
//		throw std::out_of_range("incorrect index");
//	}
//	return m_array[index];
//}
//
//
//template <typename T>
//const T & CMyArray<T>::operator[](size_t index) const
//{
//	if (index >= m_size)
//	{
//		throw std::out_of_range("incorrect index");
//	}
//	return m_array[index];
//}
//
//
//template <typename T>
//size_t CMyArray<T>::Size()const
//{
//	return m_size;
//}
//
//template <typename T>
//void CMyArray<T>::PushBack(const T & item)
//{
//	std::unique_ptr<T[]> buffer;
//	m_array.swap(buffer);
//	m_array = std::make_unique<T[]>(m_size + 1);
//	++m_size;
//	//std::copy<CMyIterator<const T>, CMyIterator<T> >(m_array.begin(), m_array.end(), std::begin(buffer.get()));
//	memcpy(m_array.get(), buffer.get(), (m_size - 1) * sizeof(T));
//	m_array[m_size - 1] = item;
//}
