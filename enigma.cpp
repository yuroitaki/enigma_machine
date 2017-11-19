#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "enigma.h"

Enigma::Enigma(int argc,char**argv){  
  create_config(argc,argv);
  create_plug_ref();
  create_rotor(config_obj->get_rotor_number());
}

Enigma::~Enigma(){
  delete plugb_ref;
  delete config_obj;
  for(auto iterator=rotor_vector.begin();iterator!=rotor_vector.end();iterator++){
    delete *iterator;
  }
}

void Enigma::encrypt(int& code){

  int len = rotor_vector.size();
  //cout << code << " ";
  plugb_ref->mapping(code,PB);
  //cout << code << endl;
  
  if (len!=0){
    Rotor* r_last = rotor_vector[len-1];
    r_last->shift_ground(RUN);
    
    for (int j=len-1;j>0;j--){
      if ((rotor_vector[j])->get_notch_stat()){
	rotor_vector[j-1]->shift_ground(RUN);
	rotor_vector[j]->set_notch_stat(false);
      }
      }
    for(int j=len-1;j>=0;j--){
      rotor_vector[j]->encrypting(code,FORWARD);
      //cout << code << " ";
      //	cout << endl;
    }
  }
  plugb_ref->mapping(code,RF);
  //    cout << code << endl;
    
  if(len!=0){
    for(int j=0;j<len;j++){
      rotor_vector[j]->encrypting(code,BACKWARD);
      //	cout << code << " ";
      //cout << endl;
    }
  }
  plugb_ref->mapping(code,PB);
  //cout<< code << " ";
  cout << static_cast<char>(code+CONVERSION) << " ";
}

void Enigma::create_rotor(int no_rotor){
  for (int i=0;i<no_rotor;i++){
    Rotor* rot = new Rotor(config_obj,i);
    rotor_vector.push_back(rot);
  }
}    

void Enigma::create_plug_ref(){
  plugb_ref = new Plugboard_Reflector(config_obj);
}

void Enigma::create_config(int argc,char**argv){
  config_obj = new Config(argc,argv);
}

void Enigma::run(){

  char charac;
  int code;
  int count = 0;
  
  while(cin >> ws >> charac){ 
    if((charac>=CONVERSION)&&(charac<=CONVERSION+25)){
      code = static_cast<int>(charac)-CONVERSION;
      encrypt(code);
      count ++;
    }else{
      throw INVALID_INPUT_CHARACTER;
    }
  }
  if ((count==0)&&(cin.fail())){
    cerr << "The input file";
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }
}
