#include "Reservoir1D.h"

Reservoir1D::Reservoir1D() :
    NumberOfCellsXDir(100), ReservoirLengthXDir(1), ReservoirLengthYDir(1), ReservoirHeightZDir(1), CellWidthXDir(1), CellArea(1), CellVolume(1)
{
    Init();
}

Reservoir1D::Reservoir1D(int numberOfCellsXDir, double reservoirLengthXDir, double reservoirLengthYDir, double reservoirHeightZDir, double cellWidthXDir) :
    NumberOfCellsXDir(numberOfCellsXDir), ReservoirLengthXDir(reservoirLengthXDir), ReservoirLengthYDir(reservoirLengthYDir),
    ReservoirHeightZDir(reservoirHeightZDir), CellWidthXDir(cellWidthXDir), CellArea(reservoirLengthYDir * reservoirHeightZDir), CellVolume(cellWidthXDir * CellArea)
{
    Init();
}

/// <summary>
/// Compute geometry of the reservoir
/// </summary>
void Reservoir1D::ComputeGeometry()
{
    for (int i = 0; i < NumberOfCellsXDir; i++)
    {
        PositionCellCenterXDir[i] = i * CellWidthXDir + CellWidthXDir / 2.0;
    }

    for (int i = 0; i < NumberOfCellsXDir + 1; i++)
    {
        PositionCellInterfaceXDir[i] = i * CellWidthXDir;
    }
}

/// <summary>
/// Allocate memory and initialize member variables
/// </summary>
void Reservoir1D::Init()
{
    PositionCellCenterXDir.resize(NumberOfCellsXDir);
    PositionCellInterfaceXDir.resize(NumberOfCellsXDir + 1);
}
