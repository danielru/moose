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

#include "Sdc.h"
#include "NonlinearSystem.h"
#include "FEProblem.h"
#include "PetscSupport.h"
#include "SdcHelper.h"

template<>
InputParameters validParams<Sdc>()
{
  InputParameters params = validParams<TimeIntegrator>();
  params.addParam<unsigned int>("niterations", 1, "Number of sdc iterations");
  params.addParam<unsigned int>("nnodes", 2, "Number of sdc quadrature nodes (Gauss-Lobatto)");
  return params;
}

Sdc::Sdc(const std::string & name, InputParameters parameters) :
    TimeIntegrator(name, parameters),
    _stage(1),
    _residual_node1(_nl.addVector("residual_node1", false, GHOSTED)),
    _residual_node2(_nl.addVector("residual_node2", false, GHOSTED)),
    _solution_start(_sys.solutionOld()),
    // At the moment, it is unclear to me how to correctly set this parameter in the input file
    _niterations(getParam<unsigned int>("niterations"))
{
        
    _residuals_ptr[0] = &_residual_node1;
    _residuals_ptr[1] = &_residual_node2;
    sdc_helper::set_weights(_nnodes, &_weights, &_nodes);
  
}

Sdc::~Sdc()
{
}

void
Sdc::computeTimeDerivatives()
{

  _u_dot  = *_solution;
  _u_dot -= _solution_old;
  _u_dot *= 1. / _dt;
  _u_dot.close();

  _du_dot_du = 1. / _dt;

  _u_dot.close();

}


void
Sdc::solve() {

  // Store solution at very beginning of step
  _solution_start = _solution_old;

  // Save time at beginning of step
  Real time_old = _fe_problem.timeOld();

  for (int k=0; k<_niterations; k++) {
    
    _console << "Sdc: Iteration " << k << std::endl;
        
    for (int m=0; m<_nnodes; m++) {
      _active_node = m;
      _fe_problem.timeOld() = _dt*_nodes[m];
     _fe_problem.time()     = _dt*_nodes[m+1];
      #ifdef LIBMESH_HAVE_PETSC
        Moose::PetscSupport::petscSetOptions(_fe_problem);
      #endif
        Moose::setSolverDefaults(_fe_problem);      
      _fe_problem.getNonlinearSystem().sys().solve();
      _fe_problem.initPetscOutput();

    }
  
  }


  // Reset time at beginning of step to its original value
  _fe_problem.timeOld() = time_old;

}


void
Sdc::postStep(NumericVector<Number> & residual)
{

    residual += _Re_time;
    residual += _Re_non_time;
    residual.close();

    *this->_residuals_ptr[_active_node] = _Re_non_time;
    this->_residuals_ptr[_active_node]->close();


}
