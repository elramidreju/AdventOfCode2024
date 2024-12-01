#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::ifstream;

int main()
{
	//ifstream infile("example01.txt");
	ifstream infile("input.txt");
	std::string line;

	std::vector<int> locationList1 = std::vector<int>();
	std::vector<int> locationList2 = std::vector<int>();
	std::vector<int> distancesList = std::vector<int>();

	// 1. Feed lists
	while (getline(infile, line))
	{
		size_t firstSpace = line.find(" ");
		int firstNumber = stoi(line.substr(0, firstSpace));
		int secondNumber = stoi(line.substr(firstSpace));
		locationList1.push_back(firstNumber);
		locationList2.push_back(secondNumber);
	}

	// 2. Sort lists
	std::sort(locationList1.begin(), locationList1.end());
	std::sort(locationList2.begin(), locationList2.end());

	// 3. Calculate distances
	int accDistance = 0;
	size_t length1 = locationList1.size();

	for (size_t i = 0; i < length1; i++)
	{
		int distance = 0;
		int a = locationList1[i];
		int b = locationList2[i];

		if (a >= b)
		{
			distance = a - b;
		}
		else
		{
			distance = b - a;
		}

		accDistance += distance;
	}

	std::cout << "Total distance is: " << accDistance << "\n";

	// 4. Calculate similarity
	int accSimilarity = 0;
	size_t length2 = locationList2.size();

	for (size_t i = 0; i < length1; i++)
	{
		int repetitions = 0;
		int locationId = locationList1[i];

		for (size_t j = 0; j < length2; j++)
		{
			if (locationId == locationList2[j])
			{
				++repetitions;
			}
		}

		accSimilarity += locationId * repetitions;
	}

	std::cout << "Total similarity is: " << accSimilarity << "\n";
}
