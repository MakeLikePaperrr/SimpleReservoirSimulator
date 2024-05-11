// SimpleReservoirSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "SimulationCase/SimulationCase.h"
#include <set>
#include <string>
#include "FileReader/InputFileReader.h"
#include "FileReader/PermeabilityFileReader.h"
#include <windows.h>

int main(int argc, char* argv[])
{
    // Valid keywords
    const std::set<std::string> validKeywords = { "" };

    // Define a map to store keyword arguments and parse command line arguments
    std::map<std::string, std::string> commandLineArgumentsAndValues;
    for (int i = 1; i < argc; ++i) 
    {
        std::string arg = argv[i];
        if (arg.substr(0, 2) == "--") 
        {
            std::string key = arg.substr(2);
            if (validKeywords.count(key)) 
            {
                // Valid keyword
                if (i + 1 < argc && argv[i + 1][0] != '-') 
                {
                    std::string value = argv[i + 1];
                    commandLineArgumentsAndValues[key] = value;
                    ++i; // Skip the value in the next iteration
                }
                else 
                {
                    std::cerr << "No value provided for keyword: " << key << std::endl;
                    return 1; // Exit with an error
                }
            }
            else 
            {
                std::cerr << "Invalid keyword: " << key << std::endl;
                return 1; // Exit with an error
            }
        }
    }

    // Check which keywords are provided and map values to correct input
    int numCellsXDir;
    if (commandLineArgumentsAndValues.count("NumCellsXDir"))
    {
        try 
        {
            numCellsXDir = std::stoi(commandLineArgumentsAndValues["NumCellsXDir"]);
        }
        catch (...)
        {
            std::cerr << "Can't parse value of keyword: " << "NumCellsXDir" << std::endl;
            return 1; // Exit with an error
        }
        
    }
    else
    {
        numCellsXDir = 100;
    }

    double cellWidthXDir;
    if (commandLineArgumentsAndValues.count("CellWidthXDir"))
    {
        try
        {
            cellWidthXDir = std::stod(commandLineArgumentsAndValues["CellWidthXDir"]);
        }
        catch (...)
        {
            std::cerr << "Can't parse value of keyword: " << "CellWidthXDir" << std::endl;
            return 1; // Exit with an error
        }
    }
    else
    {
        cellWidthXDir = 1.0;
    }

    double cellArea;
    if (commandLineArgumentsAndValues.count("CellArea"))
    {
        try
        {
            cellArea = std::stod(commandLineArgumentsAndValues["CellArea"]);
        }
        catch (...)
        {
            std::cerr << "Can't parse value of keyword: " << "CellArea" << std::endl;
            return 1; // Exit with an error
        }
    }
    else
    {
        cellArea = 1.0;
    }

    double pressureLeft;
    if (commandLineArgumentsAndValues.count("PressureLeft"))
    {
        try
        {
            pressureLeft = std::stod(commandLineArgumentsAndValues["PressureLeft"]);
        }
        catch (...)
        {
            std::cerr << "Can't parse value of keyword: " << "PressureLeft" << std::endl;
            return 1; // Exit with an error
        }
    }
    else
    {
        double pressureLeft = 1.0;
    }

    double pressureRight;
    if (commandLineArgumentsAndValues.count("PressureRight"))
    {
        try
        {
            pressureRight = std::stod(commandLineArgumentsAndValues["PressureRight"]);
        }
        catch (...)
        {
            std::cerr << "Can't parse value of keyword: " << "PressureRight" << std::endl;
            return 1; // Exit with an error
        }
    }
    else
    {
        pressureRight = 100;
    }

    double permeability;
    if (commandLineArgumentsAndValues.count("Permeability"))
    {
        try
        {
            permeability = std::stod(commandLineArgumentsAndValues["Permeability"]);
        }
        catch (...)
        {
            std::cerr << "Can't parse value of keyword: " << "Permeability" << std::endl;
            return 1; // Exit with an error
        }
    }
    else
    {
        permeability = 100.0;
    }

    std::string permeabilityFileName;
    std::vector<double> permeabilityVector;
    if (commandLineArgumentsAndValues.count("PermeabilityFileName"))
    {
        permeabilityFileName = commandLineArgumentsAndValues["PermeabilityFileName"];

        // Read permeability from file, since specified:
        PermeabilityFileReader permReader(permeabilityFileName);
        permReader.ReadDoubles();

        if (permReader.ReadFileSuccessfull)
        {
            permeabilityVector.resize(permReader.Permeability.size());
            std::fill(permeabilityVector.begin(), permeabilityVector.end(), permReader.Permeability);
        }
    }
    else
    {
        permeability = 100.0;
    }

    bool saveOutput;
    if (commandLineArgumentsAndValues.count("SaveOutput"))
    {
        std::string lowerCase;
        for (char c : commandLineArgumentsAndValues["SaveOutput"])
        {
            lowerCase += std::tolower(c);
        }
        saveOutput = lowerCase == "true" || lowerCase == "1" || lowerCase == "yes";
    }
    else
    {
        saveOutput = false;
    }

    //InputFileReader inputFileReader = InputFileReader("ValidInputFile.txt");
    //inputFileReader.ReadInputFile();

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
    for (int i = 0; i < simulationCase.IncompressibleSinglePhase1DSolver.Solution.size(); i++)
    {
        std::cout << simulationCase.IncompressibleSinglePhase1DSolver.Solution[i] << "\n";
    }
    std::cout << std::endl;

    std::cout << "Press enter key to continue...";
    std::cin.get();
}