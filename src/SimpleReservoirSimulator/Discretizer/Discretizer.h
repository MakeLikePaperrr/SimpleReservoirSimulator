#pragma once
#include <vector>

class Discretizer
{
public:
	static void ComputeTransmissibility(std::vector<double>& permeability, double cellArea, double cellWidthXDir, std::vector<double>& transmissibilityTarget);

private:
	static double ComputeInterfacePermeability(double& permeabilityLeft, double& permeabilityRight);
};

