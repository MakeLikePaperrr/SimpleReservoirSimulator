#pragma once
class RockModel
{
public:
	RockModel();
	RockModel(double referencePorosity, double referencePressure, double comnpressibility, double _permeability);

	/// <summary>
	/// Rock permeability in MiliDarcy (i.e., 1000 MiliDarcy = 1 Darcy ~= 1e-12 m2)
	/// </summary>
	double const permeability;
	double ComputePorosity(double pressure);

private:
	/// <summary>
	/// Rock compressibility in 1/Pa
	/// </summary>
	double const _compressibility;

	/// <summary>
	/// Reference pressure at which porosity is reference porosity in Pa
	/// </summary>
	double const _referencePressure;

	/// <summary>
	/// Reference porosity at reference pressure (dimensionless)
	/// </summary>
	double const _referencePorosity;
};

