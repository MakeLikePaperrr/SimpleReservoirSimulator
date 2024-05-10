#include "RockModel.h"
#include "assert.h"

RockModel::RockModel() : 
	_referencePorosity(0.3), _referencePressure(1e5), _compressibility(1e-7), permeability(100)
{
}

RockModel::RockModel(double referencePorosity, double referencePressure, double comnpressibility, double _permeability) :
	_referencePorosity(referencePorosity), _referencePressure(referencePressure), _compressibility(comnpressibility), permeability(_permeability)
{
}

double RockModel::ComputePorosity(double pressure)
{
	assert(pressure > 0);
	assert(pressure != NULL);
	return _referencePorosity * (1 - _compressibility * (_referencePressure - pressure));
}
