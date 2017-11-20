/* C++2 Assessed Exercise*/

/* The main purpose of this program is to simulate an Enigma machine. It will encrypt messages that is passed to it on the standard input stream, alongside the configuration files through the command line arguments, in which then the result will be printed on the standard output stream. Any errors caused by the configuration files or input file will cause the program to return an error code and exit. To decrypt a message, please use the exact same configuration files as to how the message was encrypted. */


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<algorithm>
#include<cctype>

using namespace std;

#include "enigma.h"

int main(int argc, char** argv){

  try{
    
  /*Construct the components of enigma and store the configuration info in each component after file checks */
    Enigma enigma_machine(argc,argv);

  /*Pass in the message from input for encryption/decryption and print the result on the output stream */
    enigma_machine.run();
  }

  catch(int err_code){
    switch(err_code){
    case INSUFFICIENT_NUMBER_OF_PARAMETERS:
      cerr <<  "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
      return 1;
    case INVALID_INPUT_CHARACTER:
      cerr << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
      return 2;
    case INVALID_INDEX:
      return 3;
    case NON_NUMERIC_CHARACTER:
      return 4;
    case IMPOSSIBLE_PLUGBOARD_CONFIGURATION:
      return 5;
    case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS:
      cerr << " number of parameters in plugboard file: plugboard.pb"<<endl;
      return 6;
    case INVALID_ROTOR_MAPPING:
      return 7;
    case NO_ROTOR_STARTING_POSITION:
      cerr << " in rotor position file: rotor.pos" << endl;
      return 8;
    case INVALID_REFLECTOR_MAPPING:
      return 9;
    case INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS:
      cerr << " number of parameters in reflector file: reflector.rf" <<endl;
      return 10;
    case ERROR_OPENING_CONFIGURATION_FILE:
      cerr << " cannot be opened correctly or it's empty (null or contains only space character)" << endl;
      return 11;
    default: cerr << "Unknown error" << endl;     
    }
  }
  return 0;
}
