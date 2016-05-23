#pragma once
#include "stdafx.h"
#include <algorithm>
#include <vector>
#include <iostream>

template <typename T>
void Sort2(T & first, T & second)
{
	if (first > second)
	{
		std::swap(first, second);
	}
}

template < typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}
	bool changed = false;
	for (auto it : arr)
	{
		if (less(maxValue, it))
		{
			changed = true;
			maxValue = it;
		}
	}
	return changed;
}
