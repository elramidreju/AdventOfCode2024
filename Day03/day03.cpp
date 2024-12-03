#include <fstream>
#include <iostream>
#include <vector>
#include "Multiplication.h"
#include "StateMachine.h"

int main()
{
	//std::ifstream infile("example01.txt");
	std::ifstream infile("input.txt");

	char symbol;
	Multiplication* mul = nullptr;
	StateMachine parser = StateMachine();
	std::vector<Multiplication*> allMuls = std::vector<Multiplication*>();

	while (infile >> std::noskipws >> symbol)
	{
		mul = parser.ReadSymbol(symbol);

		if (mul != nullptr)
		{
			allMuls.push_back(mul);
		}
	}

	int result = 0;
	for (Multiplication* mul : allMuls)
	{
		result += mul->GetResult();
	}

	std::cout << "Result (for " << allMuls.size() << " multiplications) is... " << result << "\n";
}