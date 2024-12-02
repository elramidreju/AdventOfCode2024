#include "Report.h"

Report::Report(std::vector<int> levels)
{
	_levels = std::vector<int>();
	_isSafe = true;

	int differenceTrend = 0;

	size_t length = levels.size();
	for (size_t i = 0; i < length; i++)
	{
		_levels.push_back(levels[i]);

		if (i == 0)
		{
			continue;
		}

		if (i == 1)
		{
			differenceTrend = (_levels[i] - _levels[i - 1] > 0) ? 1 : -1;
		}

		if (_isSafe)
		{
			int difference = _levels[i] - _levels[i - 1];
			bool safeMagnitude = true;
			bool safeTrend = true;

			// Check change magnitude
			int changeMagnitude = abs(difference);
			safeMagnitude = changeMagnitude >= MIN_SAFE_DIFFERENCE && changeMagnitude <= MAX_SAFE_DIFFERENCE;

			// Check change trend direction
			int previousTrend = differenceTrend;
			differenceTrend = (difference > 0) ? 1 : -1;
			safeTrend = (previousTrend > 0 && differenceTrend > 0)
				|| (previousTrend < 0 && differenceTrend < 0);

			_isSafe = safeMagnitude && safeTrend;
		}
	}
}

bool Report::IsSafe()
{
	return _isSafe;
}

bool Report::IsDampenedSafe()
{
	std::vector<Report> dampenedReports = std::vector<Report>();

	size_t length = _levels.size();
	for (size_t i = 0; i < length; i++)
	{
		std::vector<int> dampenedLevels = _levels;
		dampenedLevels.erase(dampenedLevels.begin() + i);
		dampenedReports.push_back(Report(dampenedLevels));
	}

	for (Report r : dampenedReports)
	{
		if (r.IsSafe())
		{
			return true;
		}
	}

	return false;
}
