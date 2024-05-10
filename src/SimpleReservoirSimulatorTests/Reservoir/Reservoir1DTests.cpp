#include "../pch.h"
#include "../../SimpleReservoirSimulator/Reservoir/Reservoir1D.cpp"

namespace Reservoir1DTests {
	static TEST(ComputeGeometry, Executed_CellAndInterfacePosSet) {
		// Arrange
		int numberOfCells = 10;
		double widthCellXDir = 1.0;
		double lengthReservoir = numberOfCells * widthCellXDir;
		Reservoir1D sut = Reservoir1D(numberOfCells, lengthReservoir, 1.0, 1.0, widthCellXDir);

		// Act
		sut.ComputeGeometry();

		// Assert
		EXPECT_EQ(sut.PositionCellCenterXDir.size(), numberOfCells);
		EXPECT_DOUBLE_EQ(sut.PositionCellCenterXDir[0], 0.5);
		EXPECT_DOUBLE_EQ(sut.PositionCellCenterXDir[4], 4.5);
		EXPECT_DOUBLE_EQ(sut.PositionCellCenterXDir[numberOfCells - 1], 9.5);

		EXPECT_EQ(sut.PositionCellInterfaceXDir.size(), numberOfCells + 1);
		EXPECT_DOUBLE_EQ(sut.PositionCellInterfaceXDir[0], 0.0);
		EXPECT_DOUBLE_EQ(sut.PositionCellInterfaceXDir[5], 5.0);
		EXPECT_DOUBLE_EQ(sut.PositionCellInterfaceXDir[numberOfCells], 10.0);
	}

	static TEST(Constructor, ObjectConstructed_MemberVariablesNotNull) {
		// Arrange && Act
		Reservoir1D sut = Reservoir1D();

		// Assert
		EXPECT_TRUE(sut.CellArea != NULL);
		EXPECT_TRUE(sut.CellVolume != NULL);
		EXPECT_TRUE(sut.CellWidthXDir != NULL);
		EXPECT_TRUE(sut.NumberOfCellsXDir != NULL);
		EXPECT_TRUE(sut.ReservoirHeightZDir != NULL);
		EXPECT_TRUE(sut.ReservoirLengthXDir != NULL);
		EXPECT_TRUE(sut.ReservoirLengthYDir != NULL);
	}
}

