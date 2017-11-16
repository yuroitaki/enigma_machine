#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

#include"config.h"

Config::Config(int arg_ct,char**arg_vl,const char* input_txt){
  if (arg_ct < 3)
    throw 1;
  
  arg_count = arg_ct;
  arg_value = arg_vl;
  input_file = input_txt;
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
  input_file_check();
}

void Config::input_file_check(){
  
  ifstream in_put;
  in_put.open(input_file);

  vector<int> input_code;
  char buffer;
  int num_buffer;
  
  if (in_put.fail()){
    cerr << "Input file";
    throw 11;
  }
  while(in_put>>buffer){
    num_buffer = buffer - CONVERSION;
    if ((num_buffer >= 0) && (num_buffer <=25))
      input_code.push_back(num_buffer);
    else{
      cerr << "Input file";
      throw 2;
    }
  }
  if (input_code.size()==0){
    cerr << "Input file";
    throw 2;
  }
  in_put.close();
}

const char* Config::get_file(int filecode){
  switch(filecode){
  case 1:
    return input_file;
  case 2: 
    return plugboard_file;
  case 3:
    return reflector_file;
  case 4:
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
