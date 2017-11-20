/* Header file "enigma.h" */

/* used in C++2 Assessed Exercise */

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
  void create_config(int argc,char**argv);   //create the Configuration class
  void create_plug_ref();                    //create the Plugboard & Reflector class  
  void create_rotor(int no_rotor);           //create the Rotor class
  void encrypt(int& code);                   //begin the encryption/decryption process
  void run();                                //begin passing in the message to the encryption function 
};

