#pragma once
class Viscosity
{
public:
	Viscosity();
	Viscosity(double viscosity);

	double ComputeViscosity() const;

private:
	/// <summary>
	/// Fluid viscosity in Pa.s
	/// </summary>
	double const _viscosity;
};

