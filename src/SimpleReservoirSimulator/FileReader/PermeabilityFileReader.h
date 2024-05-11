#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class PermeabilityFileReader
{
public:
	std::vector<double> Permeability;
	std::string FileName;
	bool ReadFileSuccessfull;

	PermeabilityFileReader(std::string fileName);

	void ReadDoubles();
};

