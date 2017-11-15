#include "config.h"
#include "plugboard_reflector.h"

class Enigma{
 private:
  Config* config_obj;
  vector<int> input_code;
  Plugboard_Reflector* plugb_ref;
 public:
  Enigma(Config* conf_obj,Plugboard_Reflector* pb_ref);
  void encrypt();
  void store_code(const char* input_f);
};

