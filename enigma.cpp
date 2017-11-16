#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "enigma.h"
#include "errors.h"

Enigma::Enigma(int argc,char**argv,const char* input){
  
  create_config(argc,argv,input);
  create_plug_ref();
  create_rotor(config_obj->get_rotor_number());
  store_code(config_obj->get_file(1));
}

void Enigma::encrypt(){

  int len1 = input_code.size();
  int len2 = rotor_vector.size();
  
  for (int i=0;i<len1;i++){
    cout << input_code[i] << " ";
    plugb_ref->mapping(input_code[i],2);
    cout << input_code[i] << endl;
    
    if (len2!=0){
      Rotor* r_last = rotor_vector[len2-1];
      r_last->shift_ground(1);
      
      for (int j=len2-1;j>0;j--){
	if ((rotor_vector[j])->get_notch_stat()){
	  rotor_vector[j-1]->shift_ground(1);
	  rotor_vector[j]->set_notch_stat(false);
	}
      }
      for(int j=len2-1;j>=0;j--){
	rotor_vector[j]->encrypting(input_code[i],0);
	cout << input_code[i] << " ";
	cout << endl;
      }
    }
    plugb_ref->mapping(input_code[i],3);
    cout << input_code[i] << endl;
    
    if(len2!=0){
      for(int j=0;j<len2;j++){
	rotor_vector[j]->encrypting(input_code[i],1);
	cout << input_code[i] << " ";
	cout << endl;
      }
    }
    plugb_ref->mapping(input_code[i],2);
    cout<< input_code[i] << " ";
    cout << endl;
  }
  for(int i=0;i<len1;i++){
    cout << static_cast<char>(input_code[i]+CONVERSION) << " ";
  }cout << endl << endl;
  
  delete plugb_ref;
  delete config_obj;
  
  for(auto iterator=rotor_vector.begin();iterator!=rotor_vector.end();iterator++){
    delete *iterator;
  }
  rotor_vector.clear();
}


void Enigma::store_code(const char* input_f){
  ifstream in_put;
  in_put.open(input_f);
  
  char buffer;
  int num_buffer;

  while(in_put>>buffer){
    num_buffer = buffer - CONVERSION;
    input_code.push_back(num_buffer);
  }
  in_put.close();
}

void Enigma::create_rotor(int no_rotor){
  
  for (int i=0;i<no_rotor;i++){
    Rotor* rot = new Rotor(config_obj,i);
    rotor_vector.push_back(rot);
  }
}    

void Enigma::create_plug_ref(){
  Plugboard_Reflector* pr = new Plugboard_Reflector(config_obj);
  plugb_ref = pr;
}

void Enigma::create_config(int argc,char**argv,const char* input){
  Config* cf = new Config(argc,argv,input);
  config_obj = cf;
}
