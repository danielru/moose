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

#ifndef DIRK_H
#define DIRK_H

#include "TimeIntegrator.h"

class DIRK;

template<>
InputParameters validParams<DIRK>();

/**
 * Implicit Euler's method
 */
class DIRK : public TimeIntegrator
{
public:
  DIRK(const std::string & name, InputParameters parameters);
  virtual ~DIRK();

  virtual int order() { return 1; }
  virtual void computeTimeDerivatives();
  virtual void solve();  
  virtual void postStep(NumericVector<Number> & residual);

protected:
  
  //! Indicates stage or, if _stage==3, the update step.
  unsigned int _stage;

};


#endif /* DIRK_H */
