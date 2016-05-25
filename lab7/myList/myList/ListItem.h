#pragma once
#include <iterator>

template<typename T>
class CListItem:public std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t>
{
public:
	CListItem();
	~CListItem();
	void SetNext(std::shared_ptr<CListItem> item);
	void SetPrev(std::shared_ptr<CListItem> item);

	std::shared_ptr<CListItem<T>> GetNext();
	std::shared_ptr<CListItem<T>> GetBack();
private:
	std::shared_ptr<CListItem<T>> m_next;
	std::shared_ptr<CListItem<T>> m_prev;
};

template<typename T>
CListItem<T>::CListItem()
{

}


template<typename T>
CListItem<T>::~CListItem()
{

}

template<typename T>
void CListItem<T>::SetNext(std::shared_ptr<CListItem<T>> item)
{
	next = item;
}

template<typename T>
void CListItem<T>::SetPrev(std::shared_ptr<CListItem<T>> item)
{
	prev = item;
}

template<typename T>
std::shared_ptr<CListItem<T>> CListItem<T>::GetNext()
{
	return m_next;
}

template<typename T>
std::shared_ptr<CListItem<T>> CListItem<T>::GetBack()
{
	return m_prev;
}
