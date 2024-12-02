#pragma once
#include <vector>

class Report
{
private:
	const int MIN_SAFE_DIFFERENCE = 1;
	const int MAX_SAFE_DIFFERENCE = 3;

	std::vector<int> _levels;
	bool _isSafe;
public:
	Report(std::vector<int> levels);
	bool IsSafe();
	bool IsDampenedSafe();
};
