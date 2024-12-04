#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "CharMatrix.h"

int main()
{
	//std::ifstream infile("example01.txt");
	std::ifstream infile("input.txt");
	
	std::string line;
	size_t maxLength = 0;
	size_t rowCount = 0;

	while (getline(infile, line))
	{
		maxLength = std::max(maxLength, line.size());
		rowCount++;
	}

	//std::cout << "Rows: " << rowCount << " \ Columns: " << maxLength << "\n";
	
	infile.clear();
	infile.seekg(0);

	CharMatrix matrix = CharMatrix(rowCount, maxLength);
	while (getline(infile, line))
	{
		matrix.AddRow(line);
	}

	matrix.Print();

	std::cout << "\n";
	std::cout << "Coincidences = " << matrix.CountCoincidences("MAS") << "\n";
}
