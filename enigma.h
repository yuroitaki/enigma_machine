#include "config.h"
#include "plugboard_reflector.h"
#include "rotor.h"
#include "error.h"

class Enigma{
 private:
  Config* config_obj;
  Plugboard_Reflector* plugb_ref;
  vector<Rotor*> rotor_vector;
 public:
  Enigma(int argc,char**argv);
  ~Enigma();
  void create_config(int argc,char**argv);
  void create_plug_ref();
  void create_rotor(int no_rotor);
  void encrypt(int& code);
};

