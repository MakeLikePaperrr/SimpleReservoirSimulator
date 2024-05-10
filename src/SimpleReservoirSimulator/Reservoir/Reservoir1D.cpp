#include "Reservoir1D.h"
#include <stdexcept>

Reservoir1D::Reservoir1D(RockModel rockModel) :
    NumberOfCellsXDir(100), ReservoirLengthXDir(1), ReservoirLengthYDir(1), ReservoirHeightZDir(1), CellWidthXDir(1), CellArea(1), CellVolume(1), _rockModel(rockModel)
{
    Init();
}

Reservoir1D::Reservoir1D(int numberOfCellsXDir, double reservoirLengthXDir, double reservoirLengthYDir, double reservoirHeightZDir, double cellWidthXDir, RockModel rockModel) :
    NumberOfCellsXDir(numberOfCellsXDir), ReservoirLengthXDir(reservoirLengthXDir), ReservoirLengthYDir(reservoirLengthYDir),
    ReservoirHeightZDir(reservoirHeightZDir), CellWidthXDir(cellWidthXDir), CellArea(reservoirLengthYDir * reservoirHeightZDir), CellVolume(cellWidthXDir * CellArea),
    _rockModel(rockModel)
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

void Reservoir1D::SetConstantReservoirPermeability()
{
    std::fill(ReservoirPermeability.begin(), ReservoirPermeability.end(), _rockModel.permeability);
}

void Reservoir1D::SetHeterogeneousReservoirPermeability(std::vector<double> permeability)
{
    if (permeability.size() != ReservoirPermeability.size())
    {
        throw std::invalid_argument("Size of permeability vector doesn't match size of the reservoir.");
    }
    ReservoirPermeability.assign(permeability.begin(), permeability.end());
}

void Reservoir1D::DiscretizeReservoir()
{
    Discretizer::ComputeTransmissibility(ReservoirPermeability, CellArea, CellWidthXDir, ReservoirTransmissibility);
}

/// <summary>
/// Allocate memory and initialize member variables
/// </summary>
void Reservoir1D::Init()
{
    PositionCellCenterXDir.resize(NumberOfCellsXDir);
    PositionCellInterfaceXDir.resize(NumberOfCellsXDir + 1);
    ReservoirPermeability.resize(NumberOfCellsXDir);
    ReservoirTransmissibility.resize(NumberOfCellsXDir + 1);
}
