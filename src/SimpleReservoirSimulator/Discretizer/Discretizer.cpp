#include "Discretizer.h"

/// <summary>
/// Computes interface transmissibility
/// </summary>
/// <param name="permeability">Reservoir permeability in mDarcy</param>
/// <param name="cellArea">(constant) interface area in m2</param>
/// <param name="cellWidthXDir">(constant) cellWidth in the x-direction</param>
/// <param name="transmissibilityTarget">target vector to store transmissibility values</param>
void Discretizer::ComputeTransmissibility(std::vector<double>& permeability, double cellArea, double cellWidthXDir, std::vector<double>& transmissibilityTarget)
{
	double cellInterfacePermeability;
	for (int i = 1; i < permeability.size(); i++)
	{
		cellInterfacePermeability = ComputeInterfacePermeability(permeability[i - 1], permeability[i]);
		transmissibilityTarget[i] = cellInterfacePermeability * cellArea / cellWidthXDir;
	}
}

/// <summary>
/// Compute interface permeability based on harmonic average
/// </summary>
/// <param name="permeabilityLeft">permeablity left cell in mDarcy</param>
/// <param name="permeabilityRight">permeability right cell in mDarcy</param>
/// <returns>interface permeability in mDarcy</returns>
double Discretizer::ComputeInterfacePermeability(double& permeabilityLeft, double& permeabilityRight)
{
	double cellInterfacePermeability = 2 * permeabilityLeft * permeabilityRight;
	return  cellInterfacePermeability / (permeabilityLeft + permeabilityRight);
}
