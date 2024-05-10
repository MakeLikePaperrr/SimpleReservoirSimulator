#pragma once
class Density
{
public:
	Density();
	Density(double referenceDensity, double referencePressure, double compressibility);

	double ComputeDensity(double pressure) const;

private:
	/// <summary>
	/// Compressibility constant in 1/Pa
	/// </summary>
	double const _compressibility;

	/// <summary>
	/// Reference pressure at which density = referenceDensity in Pa
	/// </summary>
	double const _referencePressure;

	/// <summary>
	/// Reference density for specific reference pressure in kg/m3
	/// </summary>
	double const _referenceDensity;
};

