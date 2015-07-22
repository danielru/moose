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

#ifndef SDC_H
#define SDC_H

#include "TimeIntegrator.h"
#include <vector>

class Sdc;

template<>
InputParameters validParams<Sdc>();

/**
 * ....
 */
class Sdc : public TimeIntegrator
{
public:
  Sdc(const std::string & name, InputParameters parameters);
  virtual ~Sdc();

  virtual int order() { return 2; }
  virtual void computeTimeDerivatives();
  virtual void solve();
  virtual void postStep(NumericVector<Number> & residual);

protected:

  //! Buffer to store non-time residual from first stage solve.
  NumericVector<Number> & _residual_node1;
 
  //! Buffer to store non-time residual from second stage solve
  NumericVector<Number> & _residual_node2;
  
  //!
  NumericVector<Number> & _sdc_rhs_node1;

  //!
  NumericVector<Number> & _sdc_rhs_node2;

  //! Maximum number allowed for number of nodes
  static const unsigned int _nodes_max = 2;

  //! Buffer to store solution at beginning of time step
  NumericVector<Number> & _solution_start;

  //! Pointers to residuals at nodes. Used to access via index
  NumericVector<Number> * _residuals_ptr[_nodes_max];
  
  //! Pointers to additional RHS terms in SDC sweep
  NumericVector<Number> * _sdc_rhs_ptr[_nodes_max];
  
  std::vector<double> _weights;
  std::vector<double> _nodes;
  
  unsigned int _niterations;
  unsigned int _nnodes;
  unsigned int _active_node;
    
};


#endif /* SDC_H */
