#include "config.h"
#include "plugboard_reflector.h"
#include "rotor.h"

class Enigma{
 private:
  Config* config_obj;
  vector<int> input_code;
  Plugboard_Reflector* plugb_ref;
  vector<Rotor*> rotor_vector;
 public:
  Enigma(int argc,char**argv,const char* input);
  
  void create_config(int argc,char**argv,const char* input);
  void create_plug_ref();
  void create_rotor(int no_rotor);
  void encrypt();
  void store_code(const char* input_f);
  
};

