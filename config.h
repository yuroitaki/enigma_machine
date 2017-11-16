#ifndef CONFIG_H
#define CONFIG_H

#include"errors.h"

class Config{
 private:
  int arg_count;
  char** arg_value;
  int rotor_count;
  const char* input_file;
  const char* plugboard_file;
  const char* reflector_file;
  vector<const char*> rotor_files;
  const char* rotor_pos_file;
  
 public:
  Config(int arg_ct,char**arg_vl,const char* input_txt);
  void input_file_check();
  const char* get_file(int filecode);
  vector<const char*>* get_rotor_files();
  int get_rotor_number();
};

#endif
