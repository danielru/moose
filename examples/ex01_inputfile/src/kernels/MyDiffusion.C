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

#include "MyDiffusion.h"
#include <cmath>

template<>
InputParameters validParams<MyDiffusion>()
{
  InputParameters p = validParams<Kernel>();
  p.set<Real>("coef")=0.0;
  return p;
}


MyDiffusion::MyDiffusion(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters), _coef(getParam<Real>("coef"))
{
  std::cout << "Instantiating MyDiffusion .... " << std::endl;
  std::cout << "Diffusion coefficient_coef = " << _coef << std::endl;
}

MyDiffusion::~MyDiffusion()
{
  std::cout << "Destructing MyDiffusion .... " << std::endl;
}

Real
MyDiffusion::computeQpResidual()
{
  Real coeff = this->getCoeff(_q_point[_qp](0), _q_point[_qp](1), _q_point[_qp](2));
  return coeff*_grad_test[_i][_qp]*_grad_u[_qp];
}

Real
MyDiffusion::computeQpJacobian()
{
  Real coeff = this->getCoeff(_q_point[_qp](0), _q_point[_qp](1), _q_point[_qp](2));
  return coeff*_grad_test[_i][_qp]*_grad_phi[_j][_qp]; 
}

Real
MyDiffusion::getCoeff(const Real x, const Real y, const Real z)
{
  // get angle in polar coordinates and transform from [-pi/2,pi/2] to [0,pi]
 Real phi = atan2(y-2.25,x-2.25) + 0.5*M_PI;
  
  // define diffusion coefficient depending on angle
 return 0.1 + 2.0*pow(sin(2*phi),2);
 
 //return 1.0;
}
