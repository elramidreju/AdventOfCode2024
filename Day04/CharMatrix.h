#pragma once
#include <string>

class CharMatrix
{
private:
	int _rows;
	int _columns;
	char* _matrix;
	char* _nextEmpty;

	int CheckPositionPart1(int x, int y, std::string lookFor);
	int CheckPositionPart2(int x, int y, std::string lookFor);
public:
	CharMatrix(int rows, int columns);
	void AddRow(std::string);
	int CountCoincidences(std::string);
	void Print();
};

