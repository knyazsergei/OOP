#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void searchNeighbors(vector<vector<char>> & matrix, pair<size_t, size_t> position)
{
	matrix[position.first][position.second] = '.';

	pair<size_t, size_t> nowPosition = position;
	/*9 diractions
	vector<pair<int, int>> squareCoordinates = {
		{ -1, -1 }, {-1,  0}, { -1, 1 },
		{ 0, -1 }, { 0, 0 },  { 0, 1 },
		{ 1, -1 },{ 1, 0 },{ 1, 1 }
	};*/
	vector<pair<int, int>> squareCoordinates = {
				  { -1, 0 },
		{ 0, -1 },{  0, 0 },{ 0, 1 },
				  {  1, 0 }
	};

	for (auto it : squareCoordinates) 
	{
		nowPosition = { position.first + it.second, position.second + it.first };
		if (nowPosition.first >= 0 &&
			nowPosition.second >= 0 &&
			nowPosition.first < matrix.size() &&
			nowPosition.second < matrix[nowPosition.first].size()
			)
		{
			if (matrix[nowPosition.first][nowPosition.second] != '.' && matrix[nowPosition.first][nowPosition.second] != '#')
			{
				searchNeighbors(matrix, nowPosition);
			}
		}
	}
}

pair<vector<vector<char>>, bool> loadMatrixFromFile(string fileName)
{
	vector<vector<char>> matrix;

	ifstream textFileInput(fileName);
	
	size_t max = 0;

	if (textFileInput.is_open())
	{
		int y = 0;
		string line;
		while (getline(textFileInput, line))
		{
			matrix.push_back({});
			matrix[y].resize(line.size());
			if (matrix[y].size() > max)
				max = matrix[y].size();
			copy(line.begin(), line.end(), matrix[y++].begin());
		}
		textFileInput.close();

		for (size_t i = 0; i < matrix.size(); i++)
		{
			matrix[i].resize(max, ' ');
		}
		return{ matrix, true };
	}	
	cout << "Error with opening file\n";
	return{ matrix, false };
}

bool saveMatrixToFile(const vector<vector<char>> & matrix, string fileName)
{
	ofstream textFileInput(fileName);
	
	if (textFileInput.is_open())
	{
		for (size_t y = 0; y < matrix.size(); ++y)
		{
			for (size_t x = 0; x < matrix[y].size(); ++x)
			{
				textFileInput << matrix[y][x];
			}
			textFileInput << endl;
		}
		textFileInput.flush();
		textFileInput.close();
		return true;
	}
	cout << "Error with opening file\n";
	return false;
}

void printMatrix(const vector<vector<char>> & matrix) 
{
	for (size_t y = 0; y < matrix.size(); ++y) 
	{
		for (size_t x = 0; x < matrix[y].size(); ++x) 
		{
			cout << matrix[y][x];
		}
		cout << endl;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 3) 
	{
		cout << "Invalid arguments, use:\nlab1.5.exe <input file> <output file>";
		return EXIT_FAILURE;
	}

	pair<vector<vector<char>>, bool> result = loadMatrixFromFile(argv[1]);

	if (!result.second) 
	{
		return EXIT_FAILURE;
	}

	auto & matrix = result.first;

	for (size_t y = 0; y < matrix.size(); ++y) 
	{
		for (size_t x = 0; x < matrix[y].size(); ++x) 
		{
			if (matrix[y][x] == 'O') 
			{
				searchNeighbors(matrix, { y, x });
				matrix[y][x] = 'O';
			}
		}
	}

	printMatrix(matrix);

	if (saveMatrixToFile(matrix, argv[2]))
	{
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}