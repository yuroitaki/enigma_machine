#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>

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

void Rotor::shift_ground(int signal){
  int len = forward_encryption.size();
  int len_n = notch.size();
  int initial_pos = 0;
  
  if(signal== SETUP){
    initial_pos = ground_position;
  }
  if(signal== RUN){
    initial_pos = 1;
  }
  int shift_space = len - initial_pos;
  vector<int> buffer_forward_encryption = forward_encryption;
  vector<int> buffer_backward_encryption = backward_encryption;
   
  for(int i=0;i<len;i++){
    if(i<initial_pos){
      forward_encryption[i+shift_space]=buffer_forward_encryption[i];
      backward_encryption[i+shift_space]=buffer_backward_encryption[i];
    }
    else{
      forward_encryption[i-initial_pos] = buffer_forward_encryption[i];
      backward_encryption[i-initial_pos] = buffer_backward_encryption[i];
    } 
  }
  if (signal==RUN){
    for(int i=0;i<len_n;i++){
      if(notch[i]==backward_encryption[0]){
	set_notch_stat(true);
	//	cout << notch[i] << "hello"<< endl;
      }
      else{
	if(notch_reached != true){
	  set_notch_stat(false);
	  //cout << "bang!" << endl;
	}
      }
    }
  }
  /*for (int i=0;i<len;i++){
    cout << forward_encryption[i] << " ";
  }cout<<endl;
  for (int i=0;i<len;i++){
    cout << backward_encryption[i] << " ";
    }cout << endl << endl;*/
}

void Rotor::encrypting(int& code, int signal){
  int len = forward_encryption.size();

  if(signal==FORWARD){
    int buffer = forward_encryption[code];
    //cout << buffer << " ";
    for (int i=0;i<len;i++){
      if (buffer == backward_encryption[i]){
	code = i;
      }
    }
  }
  if (signal==BACKWARD){
    int buffer = backward_encryption[code];
    //cout << buffer << " ";
    for (int i=0;i<len;i++){
      if(buffer == forward_encryption[i]){
	code = i;
      }
    }
  }
}

void Rotor::store_encrypt(int rotor_id){
  ifstream input_1,input_2;
  vector<const char*>* buffer_files;
  buffer_files = (config_rot->get_rotor_files());
  int buffer;
  int count = 0;
  
  input_1.open(config_rot->get_file(RP));
  vector<int> buffer_num;
  while(input_1>>buffer){
    buffer_num.push_back(buffer);
  }
  ground_position = buffer_num[rotor_id];
  input_1.close();

  input_2.open((*buffer_files)[rotor_id]);
  
  while(input_2>>buffer){
    count++;
    if(count < 27){
      forward_encryption.push_back(buffer);
    }else
      notch.push_back(buffer);
  }
  input_2.close();  
}

void Rotor:: set_notch_stat(bool stat){
  notch_reached = stat;
}

bool Rotor::get_notch_stat(){
  return notch_reached;
}

void Rotor::create_key(){
  for(int i=0;i<26;i++){
    backward_encryption.push_back(i);
  }
}
