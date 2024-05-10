// SimpleReservoirSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "SimulationCase/SimulationCase.h"

int main()
{
    std::cout << "Start program: Simple 1D reservoir simulator for single phase flow" << std::endl;

    std::cout << "Construct physics object" << std::endl;
    PhysicsModel physics = PhysicsModel();

    std::cout << "Construct reservoir object" << std::endl;
    Reservoir1D reservoir = Reservoir1D(RockModel());
    reservoir.SetConstantReservoirPermeability();

    std::cout << "Setup linear solver" << std::endl;
    Solver solver = Solver(reservoir.NumberOfCellsXDir);

    std::cout << "Create simple simulation case" << std::endl;
    SimulationCase simulationCase = SimulationCase(reservoir, physics, solver);
    simulationCase.SetupBasicSimulationCase();
    simulationCase.SolveSingleIteration();

    std::cout << "Pressure in reservoir, p = \n";
    for (int i = 0; i < solver.Solution.size(); i++)
    {
        std::cout << solver.Solution[i] << "\n";
    }
    std::cout << std::endl;

    std::cin.get();
}
