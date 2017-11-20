/* Header file "rotor.h" */

/* used in C++2 Assessed Exercise */

#include "config.h"

class Rotor{
 private:
  Config* config_rot;                       
  vector<int> forward_encryption;
  vector<int> backward_encryption;
  vector<int> notch;
  int ground_position;                        //ground position = initial position of the rotor
  int rotor_id;                               //rotor id '0' means the the leftmost rotor
  bool notch_reached;                         
 public:
  Rotor(Config* config_rotor, int rotor_idt);
  void shift_ground(int signal);              //to rotate the rotor to shift the position
  void encrypting(int& code,int signal);      //for mapping of the input letter
  void store_encrypt(int rotor_id);           //to store the mapping config
  void set_notch_stat(bool stat);             //to set the 'notch_reached' status 
  bool get_notch_stat();                      //to get the 'notch_reached' status
  void create_key();                          //to create the key/backward mapping of the forward mapping  
};
