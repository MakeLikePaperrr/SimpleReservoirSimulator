#pragma once
#include "../Reservoir/Reservoir1D.h"
#include "../PhysicsModel/PhysicsModel.h"
#include "../Solver/Solver.h"

class SimulationCase
{
public:
	Reservoir1D Reservoir;
	PhysicsModel Physics;
	Solver IncompressibleSinglePhase1DSolver;

	SimulationCase(Reservoir1D reservoir, PhysicsModel physics, Solver solver);

	void SetupBasicSimulationCase();
	void SolveSingleIteration();
};

