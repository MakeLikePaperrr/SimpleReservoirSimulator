#include "../../pch.h"
#include "../../../SimpleReservoirSimulator/PhysicsModel/Viscosity/Viscosity.cpp"
#include <vector>

namespace ViscosityTests {
	static TEST(ComputeViscosity, Executed_CorrectDensity) {
		// Arrange
		double expectedViscosity = 1e-3;

		Viscosity sut = Viscosity(expectedViscosity);

		// Act
		double actualViscosity = sut.ComputeViscosity();


		// Assert
		EXPECT_DOUBLE_EQ(actualViscosity, expectedViscosity);
	}
}