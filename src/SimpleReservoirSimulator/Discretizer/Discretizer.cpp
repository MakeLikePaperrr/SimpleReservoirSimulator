#include "Discretizer.h"

void Discretizer::ComputeTransmissibility(std::vector<double>& permeability, double cellArea, double cellWidthXDir, std::vector<double>& transmissibilityTarget)
{
	double cellInterfacePermeability;
	for (int i = 1; i < permeability.size(); i++)
	{
		cellInterfacePermeability = ComputeInterfacePermeability(permeability[i - 1], permeability[i]);
		transmissibilityTarget[i] = cellInterfacePermeability * cellArea / cellWidthXDir;
	}
}

double Discretizer::ComputeInterfacePermeability(double& permeabilityLeft, double& permeabilityRight)
{
	double cellInterfacePermeability = 2 * permeabilityLeft * permeabilityRight;
	return  cellInterfacePermeability / (permeabilityLeft + permeabilityRight);
}
