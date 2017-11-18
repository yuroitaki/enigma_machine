#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

#include"config.h"

Config::Config(int arg_ct,char**arg_vl){
  if (arg_ct < 3)
    throw 1;
  
  arg_count = arg_ct;
  arg_value = arg_vl;
  rotor_count = 0;
  
  int last_index = arg_ct-1;
  plugboard_file = arg_vl[1];
  reflector_file = arg_vl[2];
  rotor_pos_file = arg_vl[last_index];
  if (arg_ct > 3){
    for (int i=3;i<last_index;i++){
      rotor_files.push_back(arg_value[i]);
      rotor_count++;
    }
  }
}

const char* Config::get_file(int filecode){
  switch(filecode){
  case PB: 
    return plugboard_file;
  case RF:
    return reflector_file;
  case RP:
    return rotor_pos_file; 
  default: return "No files found!";
  }
}

vector<const char*>*Config::get_rotor_files(){
  return &rotor_files;
}

int Config::get_rotor_number(){
  return rotor_count;
}
