#include "PhysicsModel.h"

PhysicsModel::PhysicsModel() :
	density(Density()), viscosity(Viscosity())
{
}

PhysicsModel::PhysicsModel(Density _density, Viscosity _viscosity) :
	density(_density), viscosity(_viscosity)
{
}
