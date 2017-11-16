#include "config.h"

class Rotor{
 private:
  Config* config_rot;
  vector<int> forward_encryption;
  vector<int> backward_encryption;
  vector<int> notch;
  int ground_position;
  int rotor_id;
  bool notch_reached;
 public:
  Rotor(Config* config_rotor, int rotor_idt);
  void shift_ground(int signal);
  void encrypting(int& code,int signal);
  void store_encrypt(int rotor_id);
  void set_notch_stat(bool stat);
  bool get_notch_stat();
  void create_key();
};
