#pragma once
#include <vector>
#include "../RockModel/RockModel.h"
#include "../Discretizer/Discretizer.h"

/// <summary>
/// One dimensional reservoir class, suited for Finite Volume discretization. Unkowns are located at the cell centers.
/// Currently, assume constant cellWidth in the x-direction (i.e., dx_i = dx_i+1 = dx), as well as constant area 
/// (therefore constant volume)
/// </summary>
class Reservoir1D
{
	//         #######################################################################
	//         #         #         #         #         #         #         #         #  
	//         #   p_0   #   p_1   #   p_2   #   p_3   #   ...   #  p_N-2  #  p_N-1  # 
	//         #         #         #         #         #         #         #         #
	//         #######################################################################
	//
	//         |---> x
	//
	//         |----o---|-----o----|---------      ...     ------|----o----|----o----|
	//         0--------dx--------2dx--------      ...     -- - (N - 1)dx----(N - 1)dx---- - L
	//         
	//		# The unknowns, pressure, are actually located at 1 / 2dx, 3 / 2dx, ..., L - 3 / 2dx, L - 1 / 2dx(i.e., the center of the cell),
	//		#     while the interfaces are located at 0, dx, ..., L - dx, L.
	//		# NOTE: We have N cells, hence, N unknowns, and we have N + 1 interfaces

public:
	const int NumberOfCellsXDir;
	const double ReservoirLengthXDir;
	const double ReservoirLengthYDir;
	const double ReservoirHeightZDir;

	const double CellWidthXDir;
	const double CellArea;
	const double CellVolume;

	std::vector<double> PositionCellCenterXDir;
	std::vector<double> PositionCellInterfaceXDir;
	std::vector<double> ReservoirPermeability;
	std::vector<double> ReservoirTransmissibility;

	Reservoir1D(RockModel rockModel);
	Reservoir1D(int numberOfCellsXDir, double reservoirLengthXDir, double reservoirLengthYDir, double reservoirHeightZDir, double cellWidthXDir, RockModel rockModel);

	void ComputeGeometry();
	void SetConstantReservoirPermeability();
	void SetHeterogeneousReservoirPermeability(std::vector<double> permeability);
	void DiscretizeReservoir();

private:
	void Init();
	RockModel _rockModel;
};

