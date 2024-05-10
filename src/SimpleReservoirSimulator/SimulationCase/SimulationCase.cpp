#include "SimulationCase.h"

SimulationCase::SimulationCase(Reservoir1D reservoir, PhysicsModel physics, Solver solver) :
	Reservoir(reservoir), Physics(physics), IncompressibleSinglePhase1DSolver(solver)
{
}

void SimulationCase::SetupBasicSimulationCase()
{
	// Discretize Reservoir:
	Reservoir.DiscretizeReservoir();

	// Setup linear system:
	IncompressibleSinglePhase1DSolver.FillInnerDomainLinearSystem(Reservoir.ReservoirTransmissibility);
	IncompressibleSinglePhase1DSolver.SetStandardBoundaryConditions(1.0, 0.0);
}

void SimulationCase::SolveSingleIteration()
{
	IncompressibleSinglePhase1DSolver.SolveLinearSystem();
}
