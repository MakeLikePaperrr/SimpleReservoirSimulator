#include "../pch.h"
#include "../../SimpleReservoirSimulator/FileReader/InputFileReader.cpp"
#include <windows.h>

namespace InputFileReaderTests {
	TEST(ReadInputFile, ValidFile_FillsMapWithKeywordValuePairs) {
		// Arrange
		InputFileReader sut = InputFileReader("../../../../testFiles//ValidInputFile.txt");
		std::vector<std::string> expectedKeys = { "Permeability", "NumCellsXDir", "SaveOutput"};
		std::vector<std::string> expectedValues = { "100", "10", "true" };

		// Act
		sut.ReadInputFile();

		// Assert
		EXPECT_TRUE(sut.ReadFileSuccessfull);
		if (!sut.ReadFileSuccessfull)
			return;

		for (int i = 0; i < expectedKeys.size(); i++)
		{
			auto it = sut.KeywordValueMap.find(expectedKeys[i]);
			if (it != sut.KeywordValueMap.end())
			{
				EXPECT_TRUE(it->first == expectedKeys[i]);
				EXPECT_TRUE(it->second == expectedValues[i]);
			}
		}
	}

	TEST(ReadInputFile, InValidFile_MapWithKeywordValuePairsIsEmpty) {
		// Arrange
		InputFileReader sut = InputFileReader("../../../../testFiles//InvalidInputFile.txt");

		// Act
		sut.ReadInputFile();

		// Assert
		EXPECT_TRUE(sut.ReadFileSuccessfull);
		if (!sut.ReadFileSuccessfull)
			return;

		EXPECT_TRUE(sut.KeywordValueMap.size() == 0);
	}
}