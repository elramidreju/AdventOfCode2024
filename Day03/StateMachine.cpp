#include "StateMachine.h"
#include <iostream>

StateMachine::StateMachine()
{
	_enabled = true;
	_canEnable = false;
	_canDisable = false;
	_digits = 0;
	_first = "";
	_second = "";
	_currentState = State::START;
	_currentMultiplication = new Multiplication();
}

Multiplication* StateMachine::ReadSymbol(char c)
{
	Transition(c);
	
	if (_currentState == State::COMPLETED)
	{
		Multiplication* mul = _currentMultiplication;
		_currentMultiplication = new Multiplication();
		_currentState = State::START;

		return mul;
	}

	return nullptr;
}

void StateMachine::Transition(char c)
{
	int number;

	switch (_currentState)
	{
	case START:
		_canEnable = false;
		_canDisable = false;
		_digits = 0;
		_first = "";
		_second = "";
		if (_enabled && c == 'm')
		{
			_currentState = State::M;
		}
		else if (c == 'd')
		{
			_currentState = State::D;
		}
		break;
	
	case M:
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if (c == 'u')
		{
			_currentState = State::U;
		}
		else
		{
			_currentState = State::START;
		}
		break;
	
	case U:
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if (c == 'l')
		{
			_currentState = State::L;
		}
		else
		{
			_currentState = State::START;
		}
		break;
	
	case L:
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if (c == '(')
		{
			_currentState = State::PARENTHESES;
		}
		else
		{
			_currentState = State::START;
		}
		break;
	
	case PARENTHESES:
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if (_canEnable && c == ')')
		{
			_enabled = true;
			_currentState = State::START;
		}
		else if (_canDisable && c == ')')
		{
			_enabled = false;
			_currentState = State::START;
		}
		else
		{
			number = c - '0';
			if (number >= 0 && number <= 9)
			{
				_first += c;
				++_digits;
				_currentState = State::FIRST;
			}
			else
			{
				_currentState = State::START;
			}
		}
		break;
	
	case FIRST:
		number = c - '0';
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if(c == ',')
		{
			_digits = 0;
			_currentMultiplication->SetFirstOperand(stoi(_first));
			_currentState = State::COMMA;
		}
		else if (number >= 0 && number <= 9 && _digits < 3)
		{
			_first += c;
			++_digits;
		}
		else
		{
			_currentState = State::START;
		}
		break;
	
	case COMMA:
		number = c - '0';
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if (number >= 0 && number <= 9)
		{
			_second += c;
			++_digits;
			_currentState = State::SECOND;
		}
		else
		{
			_currentState = State::START;
		}
		break;
	
	case SECOND:
		number = c - '0';
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if (c == ')')
		{
			_currentMultiplication->SetSecondOperand(stoi(_second));
			_currentState = State::COMPLETED;
		}
		else if (number >= 0 && number <= 9 && _digits < 3)
		{
			_second += c;
			++_digits;
		}
		else
		{
			_currentState = State::START;
		}
		break;
	
	case D:
		_canEnable = false;
		_canDisable = false;
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if (c == 'o')
		{
			_currentState = State::O;
		}
		else
		{
			_currentState = State::START;
		}
		break;

	case O:
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if (c == '(')
		{
			_canEnable = true;
			_currentState = State::PARENTHESES;
		}
		else if (c == 'n')
		{
			_currentState = State::N;
		}
		else
		{
			_currentState = State::START;
		}
		break;
	
	case N:
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if (c == '\'')
		{
			_currentState = State::APOS;
		}
		else
		{
			_currentState = State::START;
		}
		break;
	
	case APOS:
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if (c == 't')
		{
			_currentState = State::T;
		}
		else
		{
			_currentState = State::START;
		}
		break;
	
	case T:
		if (c == 'd')
		{
			_currentState = State::D;
		}
		else if (c == '(')
		{
			_canDisable = true;
			_currentState = State::PARENTHESES;
		}
		else
		{
			_currentState = State::START;
		}
		break;
	
	default:
		_currentState = State::START;
		break;
	}
}
