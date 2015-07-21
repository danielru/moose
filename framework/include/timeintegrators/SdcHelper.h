#ifndef SDC_HELPER_H
#define SDC_HELPER_H

#include <vector>

class sdc_helper {

public:

  static void set_weights(int nnodes, std::vector<double>* weights, std::vector<double>* quadnodes) {
  
      (*weights).resize(nnodes*nnodes, 0.0);
      (*quadnodes).resize(nnodes, 0.0);
      
      switch (nnodes) {
      
        case 2: {
          (*weights)[0] = 0.0;
          (*weights)[1] = 0.0;
          (*weights)[2] = 0.5;
          (*weights)[3] = 0.5;
          
          (*quadnodes)[0] = 0.0;
          (*quadnodes)[1] = 1.0;
        }
        
        case 3: {
        
          (*weights)[0] = 0.0;
          (*weights)[1] = 0.0;
          (*weights)[2] = 0.0;
          (*weights)[3] = 0.208333333333333343;
          (*weights)[4] = 0.333333333333333204;
          (*weights)[5] = -0.0416666666666666574;
          (*weights)[6] = -0.0416666666666666574;
          (*weights)[7] = 0.333333333333333315;
          (*weights)[8] = 0.208333333333333259;
          
          (*quadnodes)[0] = 0.0;
          (*quadnodes)[1] = 0.5;
          (*quadnodes)[2] = 1.0;
        
        
        }
        
        case 4: {
        
          (*weights)[0] = 0.0;
          (*weights)[1] = 0.0;
          (*weights)[2] = 0.0;
          (*weights)[3] = 0.0;
          (*weights)[4] = 0.110300566479164919;
          (*weights)[5] = 0.18969943352083507;
          (*weights)[6] = -0.0339073642291438937;
          (*weights)[7] = 0.0103005664791649149;
          (*weights)[8] = -0.0372677996249964616;
          (*weights)[9] = 0.26087459737497537;
          (*weights)[10] = 0.26087459737497537;
          (*weights)[11] = -0.0372677996249964685;
          (*weights)[12] = 0.0103005664791650658;
          (*weights)[13] = -0.0339073642291438659;
          (*weights)[14] = 0.189699433520835098;
          (*weights)[15] = 0.110300566479164891;

          (*quadnodes)[0] = 0.0;
          (*quadnodes)[1] = 0.276393202250021064;
          (*quadnodes)[2] = 0.723606797749978936;
          (*quadnodes)[4] = 1.0;
        
        }
      }
  }
  
};
#endif // SDC_HELPER_H