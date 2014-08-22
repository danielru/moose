/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "Forcing.h"
#include <cmath>

template<>
InputParameters validParams<Forcing>()
{
  InputParameters p = validParams<Kernel>();
  return p;
}


Forcing::Forcing(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters)
{
  std::cout << "Instantiating Forcing .... " << std::endl;
}

Forcing::~Forcing()
{
  std::cout << "Destructing Forcing .... " << std::endl;
}

Real
Forcing::computeQpResidual()
{
  //Real coeff = this->getCoeff(_q_point[_qp](0), _q_point[_qp](1), _q_point[_qp](2));
  //return _grad_test[_i][_qp]*_grad_u[_qp];
  Real z = _q_point[_qp](2);
  Real f_i = exp(pow(z,2)/pow(0.5,2));
  Real testval = _test[_i][_qp];
  return 0.0;
}

Real
Forcing::computeQpJacobian()
{
  return 0.0; 
}