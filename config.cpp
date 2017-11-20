/* Implementation file "config.cpp" */

/* used in C++2 Assessed Exercise */

#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cctype>

using namespace std;

#include"config.h"

/*The Configuration class is similar to an input component of a machine, in which it handles and validates the configuration files of all the components  */

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
  check_pb_file();
  check_rf_file();

  if(arg_ct >3){
    for (int i=0;i<rotor_count;i++){
      check_rot_file(rotor_files[i],i);   
    }
    check_rot_pos_file();
  }
}

/*for other classes to obtain their respective config file name*/
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

/* Config File Check - each component's config file is checked separately despite the repetition of similar checking functions, as the same function differs slightly from one another to cater for each component */

/* For the file check of Reflector, Rotor & Rotor Position, the error where a file is empty or contains only white space character will be regarded as having insufficient mapping parameters */

/* for validating the plugboard config file */
void Config::check_pb_file(){
  ifstream input;
  vector<int>buffer_vec;
  int len = 0;
  int buffer;
  char charac;
  int count = 0;
  input.open(plugboard_file);

  while((count<26)&&(input>>buffer)){           
   
    input.get(charac);
    if(!isspace(charac)){                 //check if the next character is a white space char or not
      cerr << "Non-numeric character in plugboard file: plugboard.pb" <<endl;
      throw NON_NUMERIC_CHARACTER;
    } 
    if((buffer<0)||(buffer>25)){
      cerr << "Invalid index in plugboard file: plugboard.pb" <<endl;
      throw INVALID_INDEX;
    }
    buffer_vec.push_back(buffer);      //store the config value in a vector for mapping check
    len = buffer_vec.size();
    
    for (int i=0;i<len-1;i++){
      if(buffer_vec[i]==buffer_vec[len-1]){
	if((i%2==0)&&(len-1-i==1))
	  cerr <<"Invalid connection of plugboard contact "<< buffer_vec[i] << " as it is being connected to itself" << endl;
	else
	  cerr << "Invalid connection of plugboard contact "<< buffer_vec[i] << " as it is being connected to more than one other contact" <<endl;
	throw IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }count++;
  }
  if((count==26)&&(input>>charac)){            
    cerr << "Exceeded the maximum";
    throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  if((input.fail())&&(!input.eof())){            
    cerr << "Non-numeric character in plugboard file: plugboard.pb" <<endl;
    throw NON_NUMERIC_CHARACTER;
  }
  if(count%2!=0){
    cerr << "Incorrect";
    throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  input.close();
}

/* for validating the reflector config file */
void Config::check_rf_file(){
  ifstream input;
  vector<int>buffer_vec;
  int len = 0;
  int buffer;
  char charac;
  int count = 0;
  input.open(reflector_file);

  while((count<26)&&(input>>buffer)){

    input.get(charac);
    if(!isspace(charac)){
      cerr << "Non-numeric character in reflector file: reflector.rf" <<endl;
      throw NON_NUMERIC_CHARACTER;
    } 
    if((buffer<0)||(buffer>25)){
      cerr << "Invalid index in reflector file: reflector.rf" <<endl;
      throw INVALID_INDEX;
    }
    buffer_vec.push_back(buffer);
    len = buffer_vec.size();
    
    for (int i=0;i<len-1;i++){
      if(buffer_vec[i]==buffer_vec[len-1]){
	if((i%2==0)&&(len-1-i==1))
	  cerr <<"Invalid connection of reflector contact "<< buffer_vec[i] << " as it is being connected to itself" << endl;
	else
	  cerr << "Invalid connection of reflector contact "<< buffer_vec[i] << " as it is being connected to more than one other contact" << endl;
	throw INVALID_REFLECTOR_MAPPING;
      }
    }count++;
  }
  if((count==26)&&(input>>charac)){
    cerr << "Exceeded the maximum";
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  if((input.fail())&&(!input.eof())){
    cerr << "Non-numeric character in reflector file: reflector.rf" <<endl;
    throw NON_NUMERIC_CHARACTER;
  }
  if(count!=26){
    if(count%2!=0)
      cerr << "Incorrect (odd)"; 
    else
      cerr << "Insufficient";
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  input.close();
}

/* for validating the rotor config file */
void Config::check_rot_file(const char* rot_file,int rotor_id){
  ifstream input;
  vector<int>buffer1_vec;
  vector<int>buffer2_vec;
  int len1 = 0;
  int len2 = 0;
  int buffer;
  char charac;
  int count = 0;
  
  input.open(rot_file);

  while((count<52)&&(input>>buffer)){

    input.get(charac);
    if(!isspace(charac)){
      cerr << "Non-numeric character in "<< rotor_id+1 << "th rotor file" << endl; 
      throw NON_NUMERIC_CHARACTER;
    }
    if((buffer<0)||(buffer>25)){
      cerr << "Invalid index in "<< rotor_id+1 << "th rotor file" << endl;
      throw INVALID_INDEX;
    }
    if(count < 26){                    //to check if the rotor mapping is valid
      buffer1_vec.push_back(buffer);
      len1 = buffer1_vec.size();
      
      for (int i=0;i<len1-1;i++){
	if(buffer1_vec[i]==buffer1_vec[len1-1]){
	  cerr <<"Invalid mapping of input "<< len1-1 <<" to output "<<buffer1_vec[len1-1]<<  " (output " <<buffer1_vec[len1-1] << " is already mapped to from input " << i <<") in "<< rotor_id+1 << "th rotor file" << endl;
	  throw INVALID_ROTOR_MAPPING;
	}
      }
    }else{                             //to check if the notch position is valid
      buffer2_vec.push_back(buffer);
      len2 = buffer2_vec.size();
      
      for (int i=0;i<len2-1;i++){
	if(buffer2_vec[i]==buffer2_vec[len2-1]){
	  cerr <<"Repeated placing of notch "<< buffer2_vec[len2-1] << " in " << rotor_id+1 << "th rotor file" << endl;
	  throw INVALID_ROTOR_MAPPING;
	}
      }
    }
    count++;
  }
  if((count==52)&&(input>>charac)){
    cerr << "Exceeded maximum number of notches allowed in "<< rotor_id+1 << "th rotor file" << endl;
    throw INVALID_ROTOR_MAPPING;
  }
  if((input.fail())&&(!input.eof())){
    cerr << "Non-numeric character in "<< rotor_id+1 << "th rotor file" << endl;
    throw NON_NUMERIC_CHARACTER;
  }
  if(count<27){
    if(count<26)
      cerr << "Not all inputs mapped in "<< rotor_id+1 << "th rotor file" << endl;
    else
      cerr << "Missing notch position in "<< rotor_id+1 << "th rotor file" << endl;
    throw INVALID_ROTOR_MAPPING;
  }
  input.close();
}

/* for validating the rotor position config file */
void Config::check_rot_pos_file(){
  ifstream input;
  int buffer;
  int count = 0;
  char charac;
  
  input.open(rotor_pos_file);

  while((count<rotor_count)&&(input>>buffer)){
    input.get(charac);
    if(!isspace(charac)){
      cerr << "Non-numeric character in rotor position file: rotor.pos" <<endl;
      throw NON_NUMERIC_CHARACTER;
    } 
    if((buffer<0)||(buffer>25)){
      cerr << "Invalid index in rotor position file: rotor.pos" <<endl;
      throw INVALID_INDEX;
    }count++;
  }
  if((input.fail())&&(!input.eof())){
    cerr << "Non-numeric character in rotor position file: rotor.pos" <<endl;
    throw NON_NUMERIC_CHARACTER;
  }
  if(count<rotor_count){
    cerr << "No starting position for rotor " << count;
    throw NO_ROTOR_STARTING_POSITION;
  }
  input.close();
}

