#
# Testing a solution that is second order in space and first order in time.
#

[Mesh]
  type = GeneratedMesh
  dim  = 2
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
  nx   = 20
  ny   = 20
  elem_type = QUAD9
[]

[Variables]
  [./u]
    order = SECOND
    family = LAGRANGE

    [./InitialCondition]
      type = FunctionIC
      function = exact_fn
    [../]
  [../]
[]

[Functions]
  [./forcing_fn]
    type = ParsedFunction
    value = ((x*x)+(y*y))-(4*t)
  [../]

  [./exact_fn]
    type = ParsedFunction
    value = t*((x*x)+(y*y))
  [../]
[]

[Kernels]
  [./ie]
    type = TimeDerivative
    variable = u
  [../]

  [./diff]
    type = Diffusion
    variable = u
  [../]

  [./ffn]
    type = UserForcingFunction
    variable = u
    function = forcing_fn
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = u
    boundary = '0 1 2 3'
    function = exact_fn
  [../]
[]

[Postprocessors]
  [./l2_err]
    type = ElementL2Error
    variable = u
    function = exact_fn
  [../]
[]

[Executioner]
  type = Transient
#  scheme = 'dirk'
#  scheme = 'implicit-euler'
#  scheme = 'rk-2'
   scheme = 'bdf2'
  start_time = 0.0
  end_time   = 1.0
  #dt         = 0.1
  dt         = 1.0
  nl_abs_tol=1e-13
  nl_rel_tol=1e-13
[]

[Outputs]
  output_initial = false
  exodus         = false
  print_perf_log = true
[]
