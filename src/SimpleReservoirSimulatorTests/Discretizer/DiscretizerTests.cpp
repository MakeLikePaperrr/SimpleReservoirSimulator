#include "../pch.h"
#include "../../SimpleReservoirSimulator/Discretizer/Discretizer.cpp"
#include <vector>

namespace DiscretizerTests {
	TEST(ComputeTransmissibility, Executed_CorrectTransmissibilities) {
		// Assert
		std::vector<double> permeability = { 1.0, 2.0, 2.0, 0.5 };
		double cellArea = 1.0;
		double cellWidthXDir = 0.5;
		std::vector<double> expectedTransmissibility = { 0, 8.0/3.0, 4, 1.6, 0 };
		
		// Act
		std::vector<double> transmissibility(permeability.size() + 1);
		Discretizer::ComputeTransmissibility(permeability, cellArea, cellWidthXDir, transmissibility);

		// Assert
		for (int i = 0; i < expectedTransmissibility.size(); i++)
		{
			EXPECT_DOUBLE_EQ(transmissibility[i], expectedTransmissibility[i]);
		}
	}
}