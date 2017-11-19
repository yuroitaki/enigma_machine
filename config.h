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
  const char* get_file(int filecode);
  vector<const char*>* get_rotor_files();
  int get_rotor_number();
  void check_pb_file();
  void check_rf_file();
  void check_rot_file(const char* rot_file, int rotor_id);
  void check_rot_pos_file();
};

#endif
