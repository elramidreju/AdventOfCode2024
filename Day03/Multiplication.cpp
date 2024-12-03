#include "Multiplication.h"

Multiplication::Multiplication()
{
	_first = 0;
	_second = 0;
}

void Multiplication::SetFirstOperand(int operand)
{
	_first = operand;
}

void Multiplication::SetSecondOperand(int operand)
{
	_second = operand;
}

int Multiplication::GetResult()
{
	return _first * _second;
}
