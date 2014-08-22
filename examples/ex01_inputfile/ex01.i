[Mesh]
  file = mug.e
  uniform_refine = 0
[]

[Variables]
  active = 'u'

  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  active = 'diff rhs'

  [./diff]
    type = MyDiffusion
    variable = u
    coef = 0.25
  [../]
  
  [./rhs]
    type=Forcing
    variable = u
  [../]
[]

[BCs]
  active = 'bottom top'

  [./bottom]
    type = DirichletBC
    variable = u
    boundary = 'bottom'
    value = 1
  [../]

  [./top]
    type = DirichletBC
    variable = u
    boundary = 'top'
    value = -1
  [../]
[]

[Executioner]
  type = Steady

  #Preconditioned JFNK (default)
  solve_type = 'PJFNK'


[]

[Outputs]
  file_base = mydiff_out
  exodus = true
  [./console]
    type = Console
    perf_log = true
    linear_residuals = true
  [../]
[]
