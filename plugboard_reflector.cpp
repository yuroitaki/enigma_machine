/* Implementation file "plugboard_reflector.cpp" */

/* used in C++2 Assessed Exercise */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include<cctype>

using namespace std;

#include "plugboard_reflector.h"

Plugboard_Reflector::Plugboard_Reflector(Config* confg){
  config_pr = confg;
  store_config_pr(PB);
  store_config_pr(RF);
}

/*to map/reflect the input letter*/
void Plugboard_Reflector::mapping(int& code, int map_code){
  int len1 = swap_config.size();
  int len2 = ref_config.size();
  
  vector<int>* buffer_config;
  int len = 0;

  if (map_code == PB){
    len = len1;
    buffer_config = &swap_config;
  }
  if (map_code == RF){
    len = len2;
    buffer_config = &ref_config;
  }
  for(int i=0;i<len;i++){
    if (i%2==0){                          //maps the even-numbered letter to the subsequent letter
      if((*buffer_config)[i]==code){
    	code = (*buffer_config)[i+1];
	break;
      }
    }
    if (i%2!=0){                         //maps the odd-numbered letter to the previous letter
      if((*buffer_config)[i]==code){
	code = (*buffer_config)[i-1];
      }
    }
  }
}

/*to store the mapping configuration*/
void Plugboard_Reflector::store_config_pr(int store_code){
  ifstream in_put;
  in_put.open(config_pr->get_file(store_code));      //to get the file name from the class Config
  
  vector<int>* buffer_vec;
  int buffer;

  if(store_code == PB){
    buffer_vec = &swap_config;
  }
  if(store_code == RF){
    buffer_vec = &ref_config;
  }
  while(in_put>>buffer){
    buffer_vec->push_back(buffer);
  }
  in_put.close();
}

