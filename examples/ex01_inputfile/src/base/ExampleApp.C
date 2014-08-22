#include "ExampleApp.h"
#include "Moose.h"
#include "Factory.h"
#include "AppFactory.h"

// Include my own diffusion kernel
#include "MyDiffusion.h"
#include "Forcing.h"

template<>
InputParameters validParams<ExampleApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

ExampleApp::ExampleApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  ExampleApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ExampleApp::associateSyntax(_syntax, _action_factory);
  
  std::cout << "Instantiating ExampleApp .... " << std::endl;
  
}

ExampleApp::~ExampleApp()
{
  std::cout << "Destructing ExampleApp .... " << std::endl;
}

void
ExampleApp::registerObjects(Factory & factory )
{
  // register my own diffusion kernel
  registerKernel(MyDiffusion); // <- registration
  registerKernel(Forcing);
}

void
ExampleApp::registerApps()
{
  registerApp(ExampleApp);
}

void
ExampleApp::associateSyntax(Syntax& /*syntax*/, ActionFactory & /*action_factory*/)
{
}
