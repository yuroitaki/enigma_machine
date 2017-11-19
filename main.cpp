#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<algorithm>

using namespace std;

#include "enigma.h"
#include "errors.h"


int main(int argc, char** argv){

  try{
    Enigma enigma_machine(argc,argv);
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
      cerr << " has invalid index." << endl;
      return 3;
    case NON_NUMERIC_CHARACTER:
      return 4;
    case IMPOSSIBLE_PLUGBOARD_CONFIGURATION:
      cerr << "The plugboard file has impossible plugboard configuration." <<endl;
      return 5;
    case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS:
      cerr << "Non-numeric character in reflector file reflector.rf"<<endl;
      return 6;
    case INVALID_ROTOR_MAPPING:
      return 7;
    case NO_ROTOR_STARTING_POSITION:
      cerr << " in rotor position file: rotor.pos" << endl;
      return 8;
    case INVALID_REFLECTOR_MAPPING:
      cerr << "The reflector file has invalid reflector mapping." << endl;
      return 9;
    case INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS:
      cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" <<endl;
      return 10;
    case ERROR_OPENING_CONFIGURATION_FILE:
      cerr << " cannot be opened correctly." << endl;
      return 11;
    default: cerr << "Unknown error." << endl;     
    }
  }
  return 0;
}
