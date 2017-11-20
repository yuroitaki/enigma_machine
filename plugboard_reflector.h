/* Header file "plugboard_reflector.h" */

/* used in C++2 Assessed Exercise */


#include "config.h"

/* PLugboard and Reflector are assigned to the same class as both of them have exactly the same member function implementations, although perhaps this can be done better with inheritance*/

class Plugboard_Reflector{
 private:
  vector<int>swap_config;                   //container storing the mapping config of plugboard
  vector<int>ref_config;                    //container storing the mapping config of reflector
  Config* config_pr;
 public:
  Plugboard_Reflector(Config* confg);
  void store_config_pr(int store_code);       //to store the mapping configuration
  void mapping(int& code,int map_code);       //to map/reflect the input letter
};
