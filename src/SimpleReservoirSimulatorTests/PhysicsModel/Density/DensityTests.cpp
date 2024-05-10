#include "../../pch.h"
#include "../../../SimpleReservoirSimulator/PhysicsModel/Density/Density.cpp"
#include <vector>

namespace DensityTests {
	TEST(ComputeDensity, Executed_CorrectDensity) {
		// Arrange
		double referencePressure = 1.0;
		double referenceDensity = 2.0;
		double compressibility = 0.1;

		std::vector<double> actualPressure = { 2.0, 20.0, 0.1 };
		std::vector<double> expectedDensity = { 2.2, 5.8, 1.82 };
		std::vector<double> actualDensity;

		Density sut = Density(referenceDensity, referencePressure, compressibility);

		// Act
		actualDensity.resize(3);
		for (int i = 0; i < actualPressure.size(); i++)
		{
			actualDensity[i] = sut.ComputeDensity(actualPressure[i]);
		}


		// Assert
		for (int i = 0; i < actualPressure.size(); i++)
		{
			EXPECT_DOUBLE_EQ(actualDensity[i], expectedDensity[i]);
		}
	}

	TEST(ComputeDensity, InvalidValueForPressure_AssertionThrown) {
		// Arrange

		Density sut = Density();

		// Act && Assert
		ASSERT_DEATH(sut.ComputeDensity(-1), "");
	}

	TEST(ComputeDensity, PressureIsNull_AssertionThrown) {
		// Arrange

		Density sut = Density();

		// Act && Assert
		ASSERT_DEATH(sut.ComputeDensity(NULL), "");
	}
}
