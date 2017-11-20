/* Header file "config.h" */

/* used in C++2 Assessed Exercise */

#ifndef CONFIG_H
#define CONFIG_H

#include"errors.h"

class Config{
 private:
  int arg_count;
  char** arg_value;
  int rotor_count;
  const char* plugboard_file;
  const char* reflector_file;
  vector<const char*> rotor_files;
  const char* rotor_pos_file;
 public:
  Config(int arg_ct,char**arg_vl);
  const char* get_file(int filecode);       //for other classes to obtain their respective config file name
  vector<const char*>* get_rotor_files();  
  int get_rotor_number();                   // for Enigma class to obtain the number of rotors inputted
  void check_pb_file();                     // for validating the relevant config files 
  void check_rf_file();
  void check_rot_file(const char* rot_file, int rotor_id);
  void check_rot_pos_file();
};

#endif
