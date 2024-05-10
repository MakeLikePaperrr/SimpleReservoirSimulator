#include "Solver.h"

Solver::Solver(int numberOfUnknowns) :
    _numberOfUnknowns(numberOfUnknowns)
{
    Solution.resize(numberOfUnknowns);
    SetupLinearSystem();
}

/// <summary>
/// Setting up linear system based on the number of cells in the x-direction of the 1D reservoir (using Eigen linear algebra library for sparse matrices)
/// </summary>
void Solver::SetupLinearSystem()
{
    // For one-dimensional reservoir in single phase, number of unknowns (and #equations) is equal to number of cells in the x-direction 
    _linearSystem = Eigen::SparseMatrix<double>(_numberOfUnknowns, _numberOfUnknowns);
    _rightHandSide = Eigen::VectorXd::Zero(_numberOfUnknowns);
}

/// <summary>
/// Set pressure in a cell to a constant value (assumption: linear system is empty or has only diagonal terms)
/// </summary>
/// <param name="constantPressure">Constant pressure in certain cell 'cellNumber'</param>
/// <param name="cellNumber">Number of cell in which pressure has to be constant (means linear system has only a diagonal entry for this row/col)</param>
void Solver::SetConstantPressureInCell(double constantPressure, int cellNumber)
{
    if (cellNumber >= _numberOfUnknowns || cellNumber < 0)
    {
        std::stringstream ss;
        ss << "Can't set pressure of cell to constant value since cell number : " << cellNumber << ", is outside of domain of size [0, " << _numberOfUnknowns << "]";
        throw std::invalid_argument(ss.str());
    }
    // Simplification of actual boundary conditions (simply set pressure in cell constant)
    _linearSystem.insert(cellNumber, cellNumber) = 1.0;
    _rightHandSide[cellNumber] = constantPressure;
}

/// <summary>
/// Fill the inner domain of the system of equations with homogeneous transmissibility (except first and last cell, i.e., equation)
/// </summary>
/// <param name="transmissibilityCoefficient">Single value of transmissibility</param>
void Solver::FillInnerDomainLinearSystem(double transmissibilityCoefficient)
{
    for (int i = 1; i < _numberOfUnknowns - 1; i++)
    {
        FillRowLinearSystem(transmissibilityCoefficient, i);
    }
}

/// <summary>
/// Fill the inner domain of the system of equations with heterogenous transmissibility (except first and last cell, i.e., equation)
/// </summary>
/// <param name="transmissibilityCoefficients">Vector of transmissibility coefficients</param>
void Solver::FillInnerDomainLinearSystem(std::vector<double>& transmissibilityCoefficients)
{
    if (transmissibilityCoefficients.size() != _numberOfUnknowns + 1)
    {
        std::stringstream ss;
        ss << "transmissibilityCoefficients has incorrect size : " << transmissibilityCoefficients.size() << ", instead of number of unknowns + 1 = " << _numberOfUnknowns + 1;
        throw std::invalid_argument(ss.str());
    }

    for (int i = 1; i < _numberOfUnknowns - 1; i++)
    {
        FillRowLinearSystem(transmissibilityCoefficients[i], transmissibilityCoefficients[i +1], i);
    }
}

/// <summary>
/// Standard (simplified) boundary condition where first and last cell is set to constant pressure
/// </summary>
/// <param name="pressureLeft"></param>
/// <param name="pressureRight"></param>
void Solver::SetStandardBoundaryConditions(double pressureLeft, double pressureRight)
{
    SetConstantPressureInCell(pressureLeft, 0);
    SetConstantPressureInCell(pressureRight, _numberOfUnknowns - 1);
}

/// <summary>
/// Solve linear system using factorization (Eigen library)
/// </summary>
void Solver::SolveLinearSystem()
{
    _linearSystem.makeCompressed();
    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.analyzePattern(_linearSystem);
    solver.factorize(_linearSystem);
    _pressure = solver.solve(_rightHandSide);

    Eigen::Map<Eigen::VectorXd>(Solution.data(), Solution.size()) = _pressure;
}

/// <summary>
/// Add a single row to the linear system, based on single phase incompressible system, assuming heterogeneous reservoir:
/// F_in - Fout = 0, F_in = T * (P_i - P_i-1), F_out = T * (P_i+1 - P_i)
/// T * P_i-1 - 2 T * P_i + T * P_i+1 = 0
/// </summary>
/// <param name="transm">Constant geometric transmissiblity (assuming heterogeneous)</param>
/// <param name="ithRow">Equation number</param>
void Solver::FillRowLinearSystem(double& transm, int& ithRow)
{
    _linearSystem.insert(ithRow, ithRow - 1) = transm;
    _linearSystem.insert(ithRow, ithRow + 1) = transm;
    _linearSystem.insert(ithRow, ithRow) = -2 * transm;
}

/// <summary>
/// Add a single row to the linear system, based on single phase incompressible system:
/// F_in - Fout = 0, F_in = T_i-1,i * (P_i - P_i-1), F_out = T_i,i+1 * (P_i+1 - P_i)
/// T_i-1,i * P_i-1 - (T_i-1,i + T_i,i+1) * P_i + T_i,i+1 * P_i+1 = 0
/// </summary>
/// <param name="transm">Constant geometric transmissiblity (assuming heterogeneous)</param>
/// <param name="ithRow">Equation number</param>
void Solver::FillRowLinearSystem(double& transmLeft, double& transmRight, int& ithRow)
{
    _linearSystem.insert(ithRow, ithRow - 1) = transmLeft;
    _linearSystem.insert(ithRow, ithRow + 1) = transmRight;
    _linearSystem.insert(ithRow, ithRow) = - (transmLeft + transmRight);
}