#include "SimulationCase.h"

SimulationCase::SimulationCase(Reservoir1D reservoir, PhysicsModel physics, Solver solver) :
	Reservoir(reservoir), Physics(physics), IncompressibleSinglePhase1DSolver(solver)
{
}
