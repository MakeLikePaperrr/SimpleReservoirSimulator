#pragma once
#include <vector>
#include <Eigen/Sparse>

class Solver
{
public:
	Solver(int numberOfUnknowns);

	/// <summary>
	/// Contains the solution to Ax = b (A = connectivity matrix with transmissibility as coefficient, and b is source terms, while x = pressure)
	/// </summary>
	std::vector<double> Solution;

	void SetConstantPressureInCell(double constantPressure, int cellNumber);
	void FillInnerDomainLinearSystem(double transmissibilityCoefficient);
	void FillInnerDomainLinearSystem(std::vector<double>& transmissibilityCoefficients);
	void SetStandardBoundaryConditions(double pressureLeft, double pressureRight);

	void SolveLinearSystem();

private:
	int const _numberOfUnknowns;
	Eigen::SparseMatrix<double> _linearSystem;
	Eigen::VectorXd _rightHandSide;
	Eigen::VectorXd _pressure;

	void SetupLinearSystem();
	void FillRowLinearSystem(double& transm, int& ithRow);
	void FillRowLinearSystem(double& transmLeft, double& transmRight, int& ithRow);
};

