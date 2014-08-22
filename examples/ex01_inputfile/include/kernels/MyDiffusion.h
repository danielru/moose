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

#ifndef MYDIFFUSION_H
#define MYDIFFUSION_H

#include "Kernel.h"

class MyDiffusion;

template<>
InputParameters validParams<MyDiffusion>();


class MyDiffusion : public Kernel
{
public:
  MyDiffusion(const std::string & name, InputParameters parameters);
  virtual ~MyDiffusion();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  Real getCoeff(Real, Real, Real);

private:
  Real _coef;
};
  
#endif /* MYDIFFUSION_H */
