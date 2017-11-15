#include "config.h"

class Plugboard_Reflector{
 private:
  vector<int>swap_config;
  vector<int>ref_config;
  Config* config_pr;
 public:
  Plugboard_Reflector(Config* confg);
  void store_config_pr(int store_code);
  void mapping(int& code,int map_code);
};
