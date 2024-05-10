#include "../pch.h"
#include "../../SimpleReservoirSimulator/Solver/Solver.cpp"
#include <vector>

namespace SolverTests {
	TEST(IntegratedTestHomogeneousSystem1, SolvableSystem_CorrectSolution) {
		// Arrange
		Solver sut = Solver(3);
		std::vector<double> expectedPressures = { 1.0, 0.5, 0.0 };

		sut.FillInnerDomainLinearSystem(1.0);
		sut.SetStandardBoundaryConditions(1.0, 0.0);
		
		// Act
		sut.SolveLinearSystem();

		// Assert
		for (int i = 0; i < expectedPressures.size(); i++)
		{
			ASSERT_DOUBLE_EQ(sut.Solution[i], expectedPressures[i]);
		}
	}

	TEST(IntegratedTestHomogeneousSystem2, SolvableSystem_CorrectSolution) {
		// Arrange
		Solver sut = Solver(5);
		std::vector<double> expectedPressures = { 1.0, 0.75, 0.5, 0.25, 0.0 };

		sut.FillInnerDomainLinearSystem(1.0);
		sut.SetStandardBoundaryConditions(1.0, 0.0);

		// Act
		sut.SolveLinearSystem();

		// Assert
		for (int i = 0; i < expectedPressures.size(); i++)
		{
			ASSERT_DOUBLE_EQ(sut.Solution[i], expectedPressures[i]);
		}
	}

	TEST(IntegratedTestHeterogeneousSystem, SolvableSystem_CorrectSolution) {
		// Arrange
		Solver sut = Solver(5);
		std::vector<double> transmissibilities = { 1.0, 1.0, 2.0, 2.0, 0.5, 0.5 };
		std::vector<double> expectedPressures = { 1.0, 0.75, 0.625, 0.5, 0.0 };

		sut.FillInnerDomainLinearSystem(transmissibilities);
		sut.SetStandardBoundaryConditions(1.0, 0.0);

		// Act
		sut.SolveLinearSystem();

		// Assert
		for (int i = 0; i < expectedPressures.size(); i++)
		{
			ASSERT_DOUBLE_EQ(sut.Solution[i], expectedPressures[i]);
		}
	}
}
