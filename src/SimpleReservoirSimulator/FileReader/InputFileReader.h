#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <set>


class InputFileReader
{
public:
	std::unordered_map<std::string, std::string> KeywordValueMap;
	std::string FileName;
	bool ReadFileSuccessfull;

	InputFileReader(std::string fileName);

	void ReadInputFile();
	double TryParseKeyWordToDouble(std::string keyWord);
	int TryParseKeyWordToInt(std::string keyWord);
	bool ParseKeyWordToBool(std::string keyWord);

private:
	const std::set<std::string> _validKeywords = { "NumCellsXDir", "CellWidthXDir", "CellArea", "PressureLeft", "PressureRight", "Permeability", "PermeabilityFileName", "SaveOutput"};
};

