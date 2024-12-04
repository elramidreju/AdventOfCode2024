#include "CharMatrix.h"
#include <iostream>

CharMatrix::CharMatrix(int rows, int columns)
{
	_rows = rows;
	_columns = columns;
	_matrix = new char[_rows * _columns];
	_nextEmpty = _matrix;
	for (size_t i = 0; i < _rows * _columns; i++)
	{
		_matrix[i] = '_';
	}
}

void CharMatrix::AddRow(std::string line)
{
	for (char c : line)
	{
		*_nextEmpty = c;
		++_nextEmpty;
	}
}

int CharMatrix::CountCoincidences(std::string lookFor)
{
	int result = 0;

	for (size_t y = 0; y < _rows; y++)
	{
		for (size_t x = 0; x < _columns; x++)
		{
			result += CheckPositionPart2(x, y, lookFor);
		}
	}

	return result;
}

void CharMatrix::Print()
{
	int i = 0;
	size_t length = _rows * _columns;

	for (size_t j = 0; j < length; j++)
	{
		std::cout << _matrix[j];
		if ((j + 1) % _columns == 0)
		{
			std::cout << "\n";
		}
	}
}

int CharMatrix::CheckPositionPart1(int x, int y, std::string lookFor)
{
	int length = lookFor.size();
	int count = 0;
	int letters = 0;

	if (y >= length - 1) // Can't check North if there are less spaces up than letters in lookFor
	{
		// Check NORTH
		
		letters = 0;

		for (size_t i = 0; i < length; i++)
		{
			if (lookFor[i] == _matrix[((y - i) * _columns) + (x)])
			{
				++letters;
			}
		}

		if (letters == length)
		{
			++count;
		}
	}

	if (y <= _rows - length) // Can't check South if there are less spaces down than letters in lookFor
	{
		// Check SOUTH

		letters = 0;

		for (size_t i = 0; i < length; i++)
		{
			if (lookFor[i] == _matrix[((y + i) * _columns) + (x)])
			{
				++letters;
			}
		}

		if (letters == length)
		{
			++count;
		}
	}

	if (x <= _columns - length) // Can't check East if there are less spaces to the right than letters in lookFor
	{
		// Check EAST

		letters = 0;

		for (size_t i = 0; i < length; i++)
		{
			if (lookFor[i] == _matrix[(y * _columns) + (x + i)])
			{
				++letters;
			}
		}

		if (letters == length)
		{
			++count;
		}
	}

	if (x >= length - 1) // Can't check West if there are less spaces to the left than letters in lookFor
	{
		// Check WEST

		letters = 0;

		for (size_t i = 0; i < length; i++)
		{
			if (lookFor[i] == _matrix[(y * _columns) + (x - i)])
			{
				++letters;
			}
		}

		if (letters == length)
		{
			++count;
		}
	}

	if (x <= _columns - length && y >= length - 1)
	{
		// Check NORTH-EAST

		letters = 0;

		for (size_t i = 0; i < length; i++)
		{
			if (lookFor[i] == _matrix[((y - i) * _columns) + (x + i)])
			{
				++letters;
			}
		}

		if (letters == length)
		{
			++count;
		}
	}

	if (x <= _columns - length && y <= _rows - length)
	{
		// Check SOUTH-EAST

		letters = 0;

		for (size_t i = 0; i < length; i++)
		{
			if (lookFor[i] == _matrix[((y + i) * _columns) + (x + i)])
			{
				++letters;
			}
		}

		if (letters == length)
		{
			++count;
		}
	}

	if (x >= length - 1 && y >= length - 1)
	{
		// Check NORTH-WEST 

		letters = 0;

		for (size_t i = 0; i < length; i++)
		{
			if (lookFor[i] == _matrix[((y - i) * _columns) + (x - i)])
			{
				++letters;
			}
		}

		if (letters == length)
		{
			++count;
		}
	}

	if (x >= length - 1 && y <= _rows - length)
	{
		// Check SOUTH-WEST 

		letters = 0;

		for (size_t i = 0; i < length; i++)
		{
			if (lookFor[i] == _matrix[((y + i) * _columns) + (x - i)])
			{
				++letters;
			}
		}

		if (letters == length)
		{
			++count;
		}
	}

	return count;
}

int CharMatrix::CheckPositionPart2(int x, int y, std::string lookFor)
{
	// NOTE: I am limiting this to the case of "MAS" instead of making it generic

	char cne, cse, cnw, csw;

	if (x == 0 || x == _columns - 1 || y == 0 || y == _rows - 1)
	{
		// We can't start the search from a border
		return 0;
	}

	if (_matrix[(y * _columns) + x] == 'A')
	{
		cne = _matrix[((y - 1) * _columns) + (x + 1)];
		cse = _matrix[((y + 1) * _columns) + (x + 1)];
		cnw = _matrix[((y - 1) * _columns) + (x - 1)];
		csw = _matrix[((y + 1) * _columns) + (x - 1)];

		if ( ((cne == 'M' && csw == 'S') || (cne == 'S' && csw == 'M'))
			&& ((cnw == 'M' && cse == 'S') || (cnw == 'S' && cse == 'M')))
		{
			return 1;
		}
	}

	return 0;
}
