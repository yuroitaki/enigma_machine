#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cctype>

using namespace std;

#include"config.h"

Config::Config(int arg_ct,char**arg_vl){
  
  arg_count = arg_ct;
  arg_value = arg_vl;
  rotor_count = 0;

  
  if ((arg_ct < 3)||(arg_ct ==4))
    throw INSUFFICIENT_NUMBER_OF_PARAMETERS;
  
  int last_index = arg_ct-1;
  plugboard_file = arg_vl[1];
  reflector_file = arg_vl[2];
  
  if (arg_ct > 3){
    rotor_pos_file = arg_vl[last_index];
    for (int i=3;i<last_index;i++){
      rotor_files.push_back(arg_value[i]);
      rotor_count++;
    }
  }
  check_pb_rf_file(PB);
  check_pb_rf_file(RF);

  if(arg_ct >3){
    check_rot_pos_file();
    for (int i=0;i<rotor_count;i++){
      check_rot_file(rotor_files[i],i);   
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

void Config::check_pb_rf_file(int check_code){
  ifstream input;
  vector<int>buffer_vec;
  int len = 0;
  int buffer = 10;
  char buffer2;
  int count = 0;
  int config_error, parameter_error;
  const char* filename;
  const char* message;

  if (check_code == PB){
    filename = plugboard_file;
    message = "The plugboard file";
    config_error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    parameter_error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  if (check_code == RF){
    filename = reflector_file;
    message = "The reflector file";
    config_error = INVALID_REFLECTOR_MAPPING;
    parameter_error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  
  input.open(filename);

  while((count<26)&&(input>>buffer)){
    if((buffer<0)||(buffer>25)){
      cerr << message;
      throw INVALID_INDEX;
    }
    buffer_vec.push_back(buffer);
    len = buffer_vec.size();
    
    for (int i=0;i<len-1;i++){
      if(buffer_vec[i]==buffer_vec[len-1])
	throw config_error;
    }count++;
  }
  if((count==26)&&(input>>buffer2))
    throw parameter_error;

  if((len==0)||(buffer_vec[len-1]!=0)){
    if((input.fail())&&(buffer==0)){
      cerr << "Non-numeric character in reflector file reflector.rf";
      throw NON_NUMERIC_CHARACTER;
    }
  }
  if(check_code==PB){
    if(count%2!=0)
      throw parameter_error;
  }
  if(check_code==RF){
    if((input.fail())&&(count==0)){
      cerr << message;
      throw ERROR_OPENING_CONFIGURATION_FILE;
    }
    if(count!=26)
      throw parameter_error;
  }  
  input.close();
}

void Config::check_rot_file(const char* rot_file,int rotor_id){
  ifstream input;
  vector<int>buffer_vec;
  vector<int>buffer1_vec;
  vector<int>buffer2_vec;
  int len = 0;
  int len1 = 0;
  int len2 = 0;
  int buffer = 10;
  char buffer2;
  int count = 0;
  const char* message = "th rotor file";
  
  input.open(rot_file);

  while((count<52)&&(input>>buffer)){
    if((buffer<0)||(buffer>25)){
      cerr << rotor_id+1 << message;
      throw INVALID_INDEX;
    }
    buffer_vec.push_back(buffer);
    len = buffer_vec.size();
    
    if(count < 26){
      buffer1_vec.push_back(buffer);
      len1 = buffer1_vec.size();
      
      for (int i=0;i<len1-1;i++){
	if(buffer1_vec[i]==buffer1_vec[len1-1]){
	  cerr <<"Invalid mapping of input "<< len1-1 <<" to output "<<buffer1_vec[len1-1]<<  " (output" <<buffer_vec[len1-1] << " is already mapped to from input" << i <<")";
	  throw INVALID_ROTOR_MAPPING;
	}
      }
    }else{
      buffer2_vec.push_back(buffer);
      len2 = buffer2_vec.size();
      
      for (int i=0;i<len2-1;i++){
	if(buffer2_vec[i]==buffer2_vec[len2-1]){
	  cerr << rotor_id+1 << message;
	  throw INVALID_ROTOR_MAPPING;
	}
      }
    }
    count++;
  }
  if((count==52)&&(input>>buffer2)){
    cerr << rotor_id+1 << message << "more than 52";
    throw INVALID_ROTOR_MAPPING;
  }
  if((len==0)||(buffer_vec[len-1]!=0)){
    if((input.fail())&&(buffer==0)){
      cerr << "Non-numeric character for mapping in rotor file rotor.rot";
      throw NON_NUMERIC_CHARACTER;
    }
  }
  if((input.fail())&&(count==0)){
    cerr << rotor_id+1 << message;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }
  if(count<27){
    cerr << "Not all inputs mapped in rotor file: rotor.rot";
    throw INVALID_ROTOR_MAPPING;
  }
  input.close();
}

void Config::check_rot_pos_file(){
  ifstream input;
  vector<int>buffer_vec;
  int len = 0;
  int buffer = 10;
  int count = -1;
  //const char* message;
  
  input.open(rotor_pos_file);

  while((count<rotor_count)&&(input>>buffer)){
    if((buffer<0)||(buffer>25)){
      cerr << message;
      throw INVALID_INDEX;
    }
    buffer_vec.push_back(buffer);
    count++;
  }
  len = buffer_vec.size();
    
  if((len==0)||(buffer_vec[len-1]!=0)){
    if((input.fail())&&(buffer==0)){
      cerr << "Non-numeric character in rotor positions file rotor.pos"; 
      throw NON_NUMERIC_CHARACTER;
    }
  }
  /*if((input.fail())&&(count==0)){
    cerr << message;
    throw ERROR_OPENING_CONFIGURATION_FILE;
    }*/
  
  if(count<rotor_count){
    cerr << "No starting position for rotor " << count;
    throw NO_ROTOR_STARTING_POSITION;
  }
  input.close();
}

