#include "../pch.h"
#include "../../SimpleReservoirSimulator/RockModel/RockModel.cpp"
#include <vector>

namespace RockModelTests {
	TEST(ComputePorosity, Executed_CorrectPorosityAndPermeability) {
		// Arrange
		double referencePressure = 1.0;
		double referencePorosity = 0.3;
		double compressibility = 0.1;
		double permeability = 100;

		std::vector<double> actualPressure = { 2.0, 20.0, 0.1 };
		std::vector<double> expectedPorosity = { 0.33, 0.87, 0.273 };
		std::vector<double> actualPorosity;

		RockModel sut = RockModel(referencePorosity, referencePressure, compressibility, permeability);

		// Act
		actualPorosity.resize(3);
		for (int i = 0; i < actualPressure.size(); i++)
		{
			actualPorosity[i] = sut.ComputePorosity(actualPressure[i]);
		}

		// Assert
		for (int i = 0; i < actualPressure.size(); i++)
		{
			EXPECT_DOUBLE_EQ(actualPorosity[i], expectedPorosity[i]);
		}
		EXPECT_DOUBLE_EQ(permeability, sut.permeability);
	}

	TEST(ComputeDensity, InvalidValueForPressure_AssertionThrown) {
		// Arrange
		RockModel sut = RockModel();

		// Act && Assert
		ASSERT_DEATH(sut.ComputePorosity(-1), "");
	}

	TEST(ComputeDensity, PressureIsNull_AssertionThrown) {
		// Arrange
		RockModel sut = RockModel();

		// Act && Assert
		ASSERT_DEATH(sut.ComputePorosity(NULL), "");
	}
}
