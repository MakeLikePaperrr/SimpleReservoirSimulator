#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <fstream>

class InputFileReader
{
public:
	std::unordered_map<std::string, std::string> KeywordValueMap;
	std::string FileName;
	bool ReadFileSuccessfull;

	InputFileReader(std::string fileName);

	void ReadInputFile();
};

