#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <stdlib.h>

void Error(std::string text, bool & error) 
{
	std::cout << text << std::endl;
	error = true;
}

std::string Replace(const std::string & text, const std::string & searchPattern, const std::string & replacementText) 
{
	if (searchPattern.empty()) 
	{
		return text;
	}
	std::string newText;

	size_t position = 0;
	size_t oldPosition = 0;

	while ((position = text.find(searchPattern, position)) != std::string::npos) 
	{
		newText.append(text, oldPosition, position - oldPosition).append(replacementText);
		position += searchPattern.length();
		oldPosition = position;
	}
	newText.append(text, oldPosition);
	return newText;
}

bool ProcessText(const std::string & IfileName, const std::string & OfileName, const std::string & needle, const std::string & insertedRow)
{
	std::string text;
	std::ifstream textFileInput(IfileName);
	std::ofstream textFileOutput(OfileName);
	bool error = false;

	if (textFileInput.fail()) 
	{
		Error("error with opening input file", error);
		return error;
	}
	else if (textFileOutput.fail())
	{
		Error("error with opening output file", error);
		return error;
	}
	else
	{
		std::string line;
		while (getline(textFileInput, line))
		{
			text.append(Replace(line, needle, insertedRow)).append("\n");
			textFileOutput << text;
			text.clear();
		}
	}

	textFileInput.close();
	textFileOutput.close();
	return error;
}


int main(int argc, char* argv[]) 
{
	setlocale(LC_ALL, "RUS");
	bool error = false;

	if (argc != 5) 
	{
		Error("Wrong amount of arguments was proposed\nuse arguments: <input file> <output file> <search string> <replace string>", error);
		return 1;
	}

	std::string inputFileName = argv[1];
	std::string outputFileName = argv[2];
	std::string needle = argv[3];
	std::string insertedRow = argv[4];

	if (!ProcessText(inputFileName, outputFileName, needle, insertedRow)) {
		std::cout << "The program is completed with an error" << std::endl;
		return EXIT_FAILURE;
	}
	
	std::cout << "SUCCESS" << std::endl;
	return EXIT_SUCCESS;
}