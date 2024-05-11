#include "../pch.h"
#include "../../SimpleReservoirSimulator/FileReader/InputFileReader.cpp"
#include <windows.h>

namespace InputFileReaderTests {
	TEST(ReadInputFile, ValidFile_FillsMapWithKeywordValuePairs) {
		// Arrange
		InputFileReader sut = InputFileReader("../../../../testFiles/fileReaderTests/ValidInputFile.txt");
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
		InputFileReader sut = InputFileReader("../../../../testFiles/fileReaderTests/InvalidInputFile.txt");

		// Act
		sut.ReadInputFile();

		// Assert
		EXPECT_TRUE(sut.ReadFileSuccessfull);
		if (!sut.ReadFileSuccessfull)
			return;

		EXPECT_TRUE(sut.KeywordValueMap.size() == 0);
	}

	TEST(ReadInputFile, ValidFile_ParseInputCorrectly) {
		// Arrange
		InputFileReader sut = InputFileReader("../../../../testFiles/fileReaderTests/ValidInputFile.txt");
		std::vector<std::string> expectedKeys = { "Permeability", "NumCellsXDir", "SaveOutput" };
		std::vector<std::string> expectedValues = { "100", "10", "true" };
		sut.ReadInputFile();

		double expectedPerm = 100.0;
		int expectedNumCells = 10;
		bool expectedSaveOutput = true;

		// Act
		double permeability = sut.TryParseKeyWordToDouble(expectedKeys[0]);
		int numCellsXDir = sut.TryParseKeyWordToInt(expectedKeys[1]);
		bool saveOutput = sut.ParseKeyWordToBool(expectedKeys[2]);

		// Assert
		EXPECT_TRUE(sut.ReadFileSuccessfull);
		if (!sut.ReadFileSuccessfull)
			return;

		EXPECT_DOUBLE_EQ(permeability, expectedPerm);
		EXPECT_EQ(numCellsXDir, expectedNumCells);
		EXPECT_EQ(saveOutput, expectedSaveOutput);
	}
}