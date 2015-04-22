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

#include "DIRK.h"
#include "NonlinearSystem.h"
#include "FEProblem.h"
#include "PetscSupport.h"

template<>
InputParameters validParams<DIRK>()
{
  InputParameters params = validParams<TimeIntegrator>();

  return params;
}

DIRK::DIRK(const std::string & name, InputParameters parameters) :
    TimeIntegrator(name, parameters),
    _stage(1),
    _residual_stage1(_nl.addVector("residual_stage1", false, GHOSTED)),
    _residual_stage2(_nl.addVector("residual_stage2", false, GHOSTED))
{
}

DIRK::~DIRK()
{
}

void
DIRK::computeTimeDerivatives()
{
  _u_dot  = *_solution;
  
  if (_stage==1) {
  // Compute stage U_1
    _u_dot -= _solution_old;
    _u_dot *= 1 / _dt;
    
    _du_dot_du = 1.0 / _dt;
  }
  else if (_stage==2) {
  // Compute stage U_2
  }
  else if (_stage==3) {
  // Compute final update
  }
  else {
    mooseError("DIRK::computeTimeDerivatives(): Member variable _stage can only have values 1, 2 or 3.");
  }
      
  _u_dot.close();
  
}

void
DIRK::solve() {
  _stage = 1;
  _fe_problem.getNonlinearSystem().sys().solve();
 // _nl.sys().solve();
}

void
DIRK::postStep(NumericVector<Number> & residual)
{
  residual += _Re_time;
  residual += _Re_non_time;
  residual.close();
}
