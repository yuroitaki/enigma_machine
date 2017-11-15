#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "enigma.h"
#include "errors.h"

Enigma::Enigma(Config* conf_obj,Plugboard_Reflector* pb_ref){
  config_obj = conf_obj;
  plugb_ref = pb_ref;
  store_code(conf_obj->get_file(1));
}

void Enigma::encrypt(){

  //vector<int>& bp = config_obj->get_map(1);
  int len = input_code.size();
  
  for (int i=0;i<len;i++){
    cout << input_code[i] << " ";
    plugb_ref->mapping(input_code[i],2);
    cout << input_code[i] << " ";
    plugb_ref->mapping(input_code[i],3);
    cout << input_code[i] << " ";
    plugb_ref->mapping(input_code[i],2);
    cout << static_cast<char>(input_code[i]+CONVERSION) << " ";
    cout << endl;
  }
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

    


