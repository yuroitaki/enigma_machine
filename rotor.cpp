/* Implementation file "rotor.cpp" */

/* used in C++2 Assessed Exercise */

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<cctype>

using namespace std;

#include "rotor.h"

Rotor::Rotor(Config* config_rotor, int rotor_idt){
  config_rot = config_rotor;
  rotor_id = rotor_idt;
  notch_reached = false;
  store_encrypt(rotor_id);
  create_key();
  shift_ground(SETUP);
}

/*to rotate the rotor to shift the initial position*/
void Rotor::shift_ground(int signal){              
  int len = forward_encryption.size();
  int len_n = notch.size();
  int initial_pos = 0;
  
  if(signal== SETUP){           //signal to differentiate btwn the rotation during initial setup or mapping
    initial_pos = ground_position;
  }
  if(signal== RUN){
    initial_pos = 1;       //the position of the element that is going to be shifted to be the '0th' element
  }
  int shift_space = len - initial_pos;
  vector<int> buffer_forward_encryption = forward_encryption;     
  vector<int> buffer_backward_encryption = backward_encryption;
   
  for(int i=0;i<len;i++){                 //shuffle/shift function
    if(i<initial_pos){           
      forward_encryption[i+shift_space]=buffer_forward_encryption[i];
      backward_encryption[i+shift_space]=buffer_backward_encryption[i];
    }
    else{
      forward_encryption[i-initial_pos] = buffer_forward_encryption[i];
      backward_encryption[i-initial_pos] = buffer_backward_encryption[i];
    } 
  }
  if (signal==RUN){               //to check if notch is reached during mapping
    for(int i=0;i<len_n;i++){
      if(notch[i]==backward_encryption[0]){
	set_notch_stat(true);
      }
      else{
	if(notch_reached != true){ //to prevent the overwriting of notch status by subsequent notch position 
	  set_notch_stat(false);
	}
      }
    }
  }
}

/*for mapping of the input letter*/
void Rotor::encrypting(int& code, int signal){
  int len = forward_encryption.size();

  if(signal==FORWARD){                        //forward mapping function
    int buffer = forward_encryption[code];
    for (int i=0;i<len;i++){
      if (buffer == backward_encryption[i]){
	code = i;
      }
    }
  }
  if (signal==BACKWARD){                      //backward mapping function
    int buffer = backward_encryption[code];
    for (int i=0;i<len;i++){
      if(buffer == forward_encryption[i]){
	code = i;
      }
    }
  }
}

/*to store the mapping config*/
void Rotor::store_encrypt(int rotor_id){
  ifstream input_1,input_2;
  vector<const char*>* buffer_files;
  buffer_files = (config_rot->get_rotor_files());
  int buffer;
  int count = 0;
  
  input_1.open(config_rot->get_file(RP));      //function to read rotor position file
  vector<int> buffer_num;
  while(input_1>>buffer){
    buffer_num.push_back(buffer);
  }
  ground_position = buffer_num[rotor_id];
  input_1.close();

  input_2.open((*buffer_files)[rotor_id]);     //function to read rotor mapping file
  
  while(input_2>>buffer){
    count++;
    if(count < 27){
      forward_encryption.push_back(buffer);
    }else                                       //storing the notch positions
      notch.push_back(buffer);                         
  }
  input_2.close();  
}

/*to set the 'notch_reached' status */
void Rotor:: set_notch_stat(bool stat){
  notch_reached = stat;
}

/*to get the 'notch_reached' status*/
bool Rotor::get_notch_stat(){
  return notch_reached;
}

/*to create the key/backward mapping of the forward mapping  */
void Rotor::create_key(){
  for(int i=0;i<26;i++){
    backward_encryption.push_back(i);
  }
}
