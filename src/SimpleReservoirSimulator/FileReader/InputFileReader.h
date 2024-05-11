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

public:
	static const std::string NumCellsXDir;
	static const std::string CellWidthXDir;
	static const std::string CellArea;
	static const std::string PressureLeft;
	static const std::string PressureRight;
	static const std::string Permeability;
	static const std::string PermeabilityFileName;
	static const std::string SaveOutput;

	static const std::set<std::string> ValidKeywords;
};

