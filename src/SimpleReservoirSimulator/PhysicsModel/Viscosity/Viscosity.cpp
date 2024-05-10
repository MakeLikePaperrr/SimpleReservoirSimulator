#include "Viscosity.h"

Viscosity::Viscosity() :
	_viscosity(1e-3)
{
}

Viscosity::Viscosity(double viscosity) :
	_viscosity(viscosity)
{
}

/// <summary>
/// Compute fluid viscosity, currently simply returns the constant viscosity
/// </summary>
/// <returns></returns>
double Viscosity::ComputeViscosity() const
{
	return _viscosity;
}
