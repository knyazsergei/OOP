// MyArray.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "MyArray.h"

int main()
{
	CMyArray<int> arr;
	arr.Resize(10, 5);
	arr.Clear();
	arr[5];
	return 0;
}

