#pragma once
#include <exception>
#include <initializer_list>
#include "MyIterator.h"

template <typename T>
class CMyArray
{
public:

	CMyArray()
	{
		ResizeCapcity();
	}

	CMyArray(const CMyArray & arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			m_endOfCapacity = m_begin + size;
			m_end = m_begin;
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_end);
			}
			catch (...)
			{
				DestroyItems(m_begin, m_end);
				throw std::bad_alloc();
			}
		}
	}

	CMyArray(const CMyArray&& arr) :
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
			throw std::bad_alloc();
		}
	}

	CMyArray(std::initializer_list<T> values)
	{
		const auto size = values.size();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			m_endOfCapacity = m_begin + size;

			m_end = m_begin;
			try
			{
				auto current = values.begin();
				for (; current < values.end(); m_end++, current++)
				{
					new (m_end)T(*current);
				}
			}
			catch (...)
			{
				DestroyItems(m_begin, m_end);
				throw std::bad_alloc();
			}
		}
	}

	void PushBack(const T & item)
	{
		if(m_end == m_endOfCapacity)
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
			throw std::bad_alloc();
		}
	}

	void Resize(size_t size)
	{
		if (GetSize() > size)
		{
			auto end = m_end;
			m_end = m_begin + size;
			DestroyItems(m_end, end);
		}
		else if (GetSize() < size)
		{
			if (GetCapacity() < size)
			{
				ResizeCapcity(size);
			}

			auto end = m_end;
			m_end = m_begin + size;

			try
			{
				auto current = end;
				for (; current != m_end; current++)
				{
					new (current)T();
				}
			}
			catch(...)
			{
				throw std::bad_alloc();
			}
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
		ResizeCapcity(0);
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
		Clear();
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			m_endOfCapacity = m_begin + size;
			m_end = m_begin;
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_end);
			}
			catch (...)
			{
				DestroyItems(m_begin, m_end);
				throw std::bad_alloc();
			}
		}
		return (*this);
	}

	CMyArray<T> & operator=(std::initializer_list<T> values)
	{
		Clear();
		const auto size = values.size();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			m_endOfCapacity = m_begin + size;

			m_end = m_begin;
			try
			{
				auto current = values.begin();
				for (; current < values.end(); m_end++, current++)
				{
					new (m_end)T(*current);
				}
			}
			catch (...)
			{
				DestroyItems(m_begin, m_end);
				throw std::bad_alloc();
			}
		}
	}

	CMyArray<T> & operator=(const CMyArray<T> && arr)
	{
		Clear();
		m_begin = arr.m_begin;
		m_end = arr.m_end;
		m_endOfCapacity = arr.m_endOfCapacity;
		return *this;
	}

	//type cast 
	template < typename NewTypeT >
	operator CMyArray< NewTypeT >()
	{
		CMyArray< NewTypeT > result;
		result.Resize<NewTypeT>(GetSize());
		try
		{
			auto current = m_begin;
			for (size_t i = 0; current < m_end; current++, i++)
			{
				result[i] = static_cast<NewTypeT>(*current);
			}
		}
		catch (...)
		{
			result.Clear();
			throw;
		}
		return result;
	}

	template< typename NewTypeT >
	CMyArray(const CMyArray< NewTypeT > & values)
	{
		auto m_newBegin = RawAlloc(values.GetSize());
		auto currentInNew = m_newBegin;
		try
		{
			for (size_t i = 0; i < values.GetSize(); ++i, ++currentInNew)
			{
				new (currentInNew)T(static_cast<NewTypeT>(values[i]));
			}
			Clear();
			m_begin = m_newBegin;
			m_end = currentInNew;
			m_endOfCapacity = currentInNew;
		}
		catch (...)
		{
			DestroyItems(m_newBegin, currentInNew);
			throw;
		}
	}

	template < typename NewTypeT >
	CMyArray & operator=(const CMyArray< NewTypeT > & values)
	{
		auto m_newBegin = RawAlloc(values.GetSize());
		auto currentInNew = m_newBegin;
		try
		{
			for (size_t i = 0; i < values.GetSize(); ++i, ++currentInNew)
			{
				new (currentInNew)T(static_cast<NewTypeT>(values[i]));
			}
			Clear();
			m_begin = m_newBegin;
			m_end = currentInNew;
			m_endOfCapacity = currentInNew;
		}
		catch (...)
		{
			DestroyItems(m_newBegin, m_newBegin);
			throw;
		}
		return *this;
	}
	

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
			throw std::out_of_range("Array is empty (" + std::to_string(GetSize()) + ")");
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
		if (size > 0)
		{
			T * begin = RawAlloc(size);
			T * current = begin;
			auto countOfItems = GetSize();
			if (countOfItems != 0)
			{
				try {
					//Копируем старые элементы
					CopyItems(m_begin, m_end, current);
					//удаляем старые элементы
					DestroyItems(m_begin, m_end);
					RawDealloc();
				}
				catch (...)
				{
					DestroyItems(begin, current);
					throw std::bad_alloc();
				}
			}
			//Присваиваем новые значения
			m_begin = begin;
			m_endOfCapacity = m_begin + size;
			m_end = current;
		}
		else
		{
			DestroyItems(m_begin, m_end);
			RawDealloc();
			m_begin = nullptr;
			m_end = nullptr;
			m_endOfCapacity = nullptr;
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
			(--end)->~T();
		}
	}

	T * RawAlloc(size_t n)
	{
		if (!n)
		{
			return nullptr;
		}
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	void RawDealloc()
	{
		if (m_begin)
		{
			::operator delete((void*)m_begin);
		}
	}

	static const unsigned MINIMUM_CAPACITY = 0;
	T * m_begin = nullptr;
	T * m_end = nullptr;
	T * m_endOfCapacity = nullptr;
};