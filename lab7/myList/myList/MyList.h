#pragma once
#include "stdafx.h"
#include <memory>
#include "ListItem.h"

template<typename T>
class CMyList
{
public:
	CMyList();
	~CMyList();
	void push_pack(const T & item);
	void push_front(const T & item);

	void pop_pack();
	void pop_front();

	size_t size();
private:
	size_t size = 0;
	std::shared_ptr<CListItem<T>> m_first;
	std::shared_ptr<CListItem<T>> m_last;
};

template<typename T>
void CMyList<T>::pop_front()
{
	m_first->next
}

template<typename T>
void CMyList<T>::pop_pack()
{

}

template<typename T>
size_t CMyList<T>::size()
{
	return size;
}

template<typename T>
void CMyList<T>::push_pack(const T & item)
{
	++size;
	if (count == 0)
	{
		m_first = std::make_shared<T>(item);
		m_last = m_first;
		return;
	}
	m_last->SetNext(std::make_shared<T>(item));
}

template<typename T>
void CMyList<T>::push_front(const T & item)
{
	++size;
	if (count == 0)
	{
		m_first = std::make_shared<T>(item);
		m_last = m_first;
		return;
	}
	m_last->SetPrev(std::make_shared<T>(item));
}