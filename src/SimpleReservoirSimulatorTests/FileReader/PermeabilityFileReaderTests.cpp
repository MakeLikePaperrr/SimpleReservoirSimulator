#include "../pch.h"
#include "../../SimpleReservoirSimulator/FileReader/PermeabilityFileReader.cpp"

namespace PermeabilityFileReaderTests {
	TEST(ReadInputFile, ValidFile_StoresPermeabilityValuesAsDouble) {
		// Arrange
		PermeabilityFileReader sut = PermeabilityFileReader("../../../../testFiles/fileReaderTests/ValidPermeabilityFile.txt");
		std::vector<double> expectedValues = { 101.2, 25.6, 16.2, 1006.9 };

		// Act
		sut.ReadDoubles();

		// Assert
		EXPECT_TRUE(sut.ReadFileSuccessfull);
		if (!sut.ReadFileSuccessfull)
			return;

		EXPECT_TRUE(sut.Permeability.size() == expectedValues.size());
		for (int i = 0; i < expectedValues.size(); i++)
		{
			EXPECT_DOUBLE_EQ(sut.Permeability[i], expectedValues[i]);
		}
	}

	TEST(ReadInputFile, InValidFile_PermeabilityVectorRemainsEmpty) {
		// Arrange
		PermeabilityFileReader sut = PermeabilityFileReader("../../../../testFiles/fileReaderTests/InvalidPermeabilityFile.txt");

		// Act
		sut.ReadDoubles();

		// Assert
		EXPECT_TRUE(sut.ReadFileSuccessfull);
		if (!sut.ReadFileSuccessfull)
			return;

		EXPECT_TRUE(sut.Permeability.size() == 0);
	}
}