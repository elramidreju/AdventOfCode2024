#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Report.h"

int main()
{
	//std::ifstream infile("example01.txt");
	std::ifstream infile("input.txt");
	std::string line;

	std::vector<Report> reports = std::vector<Report>();

	while (getline(infile, line))
	{
		std::vector<std::string> tokens;
		boost::split(tokens, line, [](char c) {return c == ' ';});
		
		std::vector<int> levels = std::vector<int>();
		for (std::string s : tokens)
		{
			levels.push_back(stoi(s));
		}

		Report r = Report(levels);
		reports.push_back(r);
	}

	size_t safeReports = 0;
	for (Report report : reports)
	{
		if (report.IsSafe())
		{
			++safeReports;
		}
		else if (report.IsDampenedSafe())
		{
			++safeReports;
		}
	}

	std::cout << "# of Safe Reports: " << safeReports << "\n";
}
