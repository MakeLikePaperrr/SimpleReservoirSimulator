#pragma once
#include "Density/Density.h"
#include "Viscosity/Viscosity.h"

class PhysicsModel
{
public:
	PhysicsModel();
	PhysicsModel(Density density, Viscosity viscosity);

	Density density;
	Viscosity viscosity;
};

