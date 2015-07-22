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
  params.addParam<unsigned int>("niterations", 5, "Number of sdc iterations");
  params.addParam<unsigned int>("nnodes", 2, "Number of sdc quadrature nodes (Gauss-Lobatto)");
  return params;
}

Sdc::Sdc(const std::string & name, InputParameters parameters) :
    TimeIntegrator(name, parameters),
    _residual_node1(_nl.addVector("residual_node1", false, GHOSTED)),
    _residual_node2(_nl.addVector("residual_node2", false, GHOSTED)),
    _residual_aux( _nl.addVector("residual_aux", false, GHOSTED)),
    _sdc_rhs_node1( _nl.addVector("sdc_rhs_node1", false, GHOSTED)),
    _sdc_rhs_node2( _nl.addVector("sdc_rhs_node2", false, GHOSTED)),
    _solution_start(_sys.solutionOld()),
    // At the moment, it is unclear to me how to correctly set this parameter in the input file
    _niterations(getParam<unsigned int>("niterations")),
    _nnodes(getParam<unsigned int>("nnodes")),
    _active_node(0)
{
        
    if (_nnodes > _nodes_max) mooseError("Number of requested SDC nodes larger than maximum number implemented");
    
    _residuals_ptr[0] = &_residual_node1;
    _residuals_ptr[1] = &_residual_node2;
    _sdc_rhs_ptr[0]   = &_sdc_rhs_node1;
    _sdc_rhs_ptr[1]   = &_sdc_rhs_node2;
    sdc_helper::set_weights(_nnodes, &_weights, &_nodes);
    
    std::cout << _nodes[0] << " -- " << _nodes[1] << std::endl;
}

Sdc::~Sdc()
{
}

int
Sdc::order()
{
  // For Gauss-Lobatto nodes, order of quadrature is 2*_nnodes-2
  if (_niterations < 2*_nnodes-2 ) return _niterations;
  else return 2*_nnodes-2;
  
}

void
Sdc::computeTimeDerivatives()
{

  _u_dot  = *_solution;

  if (_active_node==0) _u_dot -= _solution_start;
  else  _u_dot -= _solution_old;
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
        
    for (int m=1; m<_nnodes; m++) {

      _active_node = m;
     
      _fe_problem.timeOld() = time_old + _dt*_nodes[m-1];
      _fe_problem.time()    = time_old + _dt*_nodes[m];
      
      std::cout << "Step from " << _fe_problem.timeOld() << " to " << _fe_problem.time() << std::endl;

      #ifdef LIBMESH_HAVE_PETSC
      Moose::PetscSupport::petscSetOptions(_fe_problem);
      #endif
      Moose::setSolverDefaults(_fe_problem);      
      _fe_problem.getNonlinearSystem().sys().solve();
      _fe_problem.initPetscOutput();

    }
    
    this->updateSdcRhs(_dt);
  
  }

  // Reset time at beginning of step to its original value
  _fe_problem.timeOld() = time_old;

}

void
Sdc::postStep(NumericVector<Number> & residual)
{

    residual += _Re_time;
    residual += _Re_non_time;
    // Add SDC right hand side contribution for active node
    residual -= *_sdc_rhs_ptr[_active_node];
    residual.close();

    // Non-time residual in MOOSE formulation F(u) = Re_time + Re_non_time = 0 
    // corresponds to -f(u(t),t) in IVP formulation u_t = f(u(t),t)
    *this->_residuals_ptr[_active_node] = (_Re_non_time);
    *this->_residuals_ptr[_active_node] *= (-1.0);
    this->_residuals_ptr[_active_node]->close();


}

void
Sdc::updateSdcRhs(double dt)
{
  
  for (int m=0; m<_nnodes; m++) {
  
    *_sdc_rhs_ptr[m] = *_residuals_ptr[m];
    *_sdc_rhs_ptr[m] *= -dt*_nodes[m];
  
    for (int n=0; n<_nnodes; n++) {
      _residual_aux = *_residuals_ptr[m];
      _residual_aux *= dt;
      _residual_aux *= _weights[ getIndex(n,m) ];
      *_sdc_rhs_ptr[m] += _residual_aux;
    }
  }
}

/**
 *
 */
unsigned int 
Sdc::getIndex( unsigned int i, unsigned int j) {
  return i + j*_nnodes;
}
