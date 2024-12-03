#pragma once
#include "Multiplication.h"
#include <string>

enum State
{
	START = 0,
	M = 1,
	U = 2,
	L = 3,
	PARENTHESES = 4,
	FIRST = 5,
	COMMA = 6,
	SECOND = 7,
	COMPLETED = 8,
	D = 9,
	O = 10,
	N = 11,
	APOS = 12,
	T = 13,
};

class StateMachine
{
private:
	bool _enabled;
	bool _canEnable;
	bool _canDisable;
	int _digits;
	std::string _first;
	std::string _second;
	State _currentState;
	Multiplication* _currentMultiplication;
	void Transition(char c);

public:
	StateMachine();
	Multiplication* ReadSymbol(char c);
};

