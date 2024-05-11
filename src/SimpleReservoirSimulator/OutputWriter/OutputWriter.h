#pragma once
#include <vector>
#include <string>
#include <iostream>

class OutputWriter
{
public:
	static void WriteSolutionToFile(std::vector<double> solution);

private:
	static std::string GenerateUniqueGuid();
};

