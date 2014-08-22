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

#ifndef FORCING_H
#define FORCING_H

#include "Kernel.h"

class Forcing;

template<>
InputParameters validParams<Forcing>();


class Forcing : public Kernel
{
public:
  Forcing(const std::string & name, InputParameters parameters);
  virtual ~Forcing();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

};
  
#endif /* FORCING_H */
