#include "Density.h"
#include "assert.h"

Density::Density() :
	_referenceDensity(1000), _referencePressure(1e5), _compressibility(1e-6)
{
}

Density::Density(double referenceDensity, double referencePressure, double compressibility) :
	_referenceDensity(referenceDensity), _referencePressure(referencePressure), _compressibility(compressibility)
{
}

/// <summary>
/// Simple linear compressibility model for density as a function of pressure
/// </summary>
/// <param name="pressure">Pressure in Pa</param>
/// <returns></returns>
double Density::ComputeDensity(double pressure) const
{
	assert(pressure > 0);
	assert(pressure != NULL);
	return _referenceDensity * (1 - _compressibility * (_referencePressure - pressure));
}
