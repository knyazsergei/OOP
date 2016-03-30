/*
������������ � ������������� ������ vector ���������� STL, � ����� � ��������� ����������� STL.
������������ ���������, ����������� ���������� ������� ����� � ��������� �������, ����������� ���������, �� ������������ ������ ����� � vector, �������������� ��� �������� ������� ������ �������� � ��������� � ����������� ����� ���������� ������ (����������� ���������). � ��������� ������ ���� �������� �������, ����������� ���������� �������, ��� ��������� � ����� ����������.
��� ������������ ��������������� ������� ������ ���� ����������� �����, ����������� ������������ �� ������ �� ��������� �������� ������ ������� ����������.


������ ������� ������� ������ ���� ������� �� ����������� ������� ��������� �������
*/

#include "stdafx.h"
#include "ProcessVector.h"

using namespace std;
using namespace std::placeholders;

vector<double> getDataFromStream(istream & stream);

vector<string> & split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

vector<double> getDataFromFile(string fileName)
{
	ifstream inputFile(fileName);
	if (!inputFile.is_open())
	{
		cout << "Problem with opening file";
		return{};
	}
	return getDataFromStream(inputFile);
}

vector<double> getDataFromStream(istream & stream)
{
	string line;
	vector<double> numbers;
	vector<string> strNumbers;
	while (getline(stream, line) && line != "")
	{
		strNumbers = split(line, ' ');
		for (auto it : strNumbers)
		{
			numbers.push_back(atof(it.c_str()));
		}
		strNumbers.clear();
	}
	return numbers;
}

int main(int argc, char * argv[])
{
	//use for get data from file
	/*
	if (argc != 2) {
		cout << "Wrong arguments, use: baseVector.exe <input file name>";
		return EXIT_FAILURE;
	}
	vector<double> numbers = getDataFromFile(argv[1]);
	*/
	//use for cin
	auto numbers = getDataFromStream(cin);

	
	ProcessVector(numbers);
	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, " "));
	sort(numbers.begin(), numbers.end(), [](double a, double b) {return (a < b); });
	return EXIT_SUCCESS;
}