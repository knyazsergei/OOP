#pragma once
//
//template<typename T>
//class CMyArray;
//
//template<typename T>
//class CMyIterator  : public std::iterator<std::input_iterator_tag, T>
//{
//	friend class CMyIterator;
//private:
//	CMyIterator(T* p);
//public:
//	CMyIterator(const CMyIterator &it);
//
//	bool operator!=(CMyIterator const& other) const;
//	bool operator==(CMyIterator const& other) const;
//	//typename CMyIterator::reference operator*() const;
//	CMyIterator& operator++();
//private:
//	T* p;
//};
//
//template<typename T>
//CMyIterator<T>::CMyIterator(T *p) :
//	p(p)
//{
//
//}
//
//template<typename T>
//CMyIterator<T>::CMyIterator(const CMyIterator& it) :
//	p(it.p)
//{
//
//}
//
//template<typename T>
//bool CMyIterator<T>::operator!=(CMyIterator const& other) const
//{
//	return p != other.p;
//}
//
//template<typename T>
//bool CMyIterator<T>::operator==(CMyIterator const& other) const
//{
//	return p == other.p;
//}
//
////template<typename T>
////typename CMyIterator<T>::reference CMyIterator<T>::operator*() const
////{
////	return *p;
////}
//
//template<typename T>
//CMyIterator<T> &CMyIterator<T>::operator++()
//{
//	++p;
//	return *this;
//}
//
