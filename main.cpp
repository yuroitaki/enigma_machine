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

    char charac;
    int code;

    if(cin.fail()){
      throw ERROR_OPENING_CONFIGURATION_FILE;
    }
    while(cin >> charac){ 
      if((charac>=CONVERSION)&&(charac<=CONVERSION+25)){
	code = static_cast<int>(charac)-CONVERSION;
	enigma_machine.encrypt(code);
      }else{
	throw INVALID_INPUT_CHARACTER;
      }
    }
  }
	    
  catch(int err_code){
    switch(err_code){
    case INSUFFICIENT_NUMBER_OF_PARAMETERS:
      cerr <<  "There is an insufficient number of parameters from the input configuration files." << endl;
      return 1;
    case INVALID_INPUT_CHARACTER:
      cerr << "The input file has invalid input character." << endl;
      return 2;
    case INVALID_INDEX:
	cerr << " has invalid index." << endl;
	return 3;
    case NON_NUMERIC_CHARACTER:
      cerr << " has non-numeric character." << endl;
      return 4;
    case IMPOSSIBLE_PLUGBOARD_CONFIGURATION:
      cerr << " has impossible plugboard configuration." <<endl;
      return 5;
    case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS:
      cerr << " has incorrect number of plugboard parameters."<<endl;
      return 6;
    case INVALID_ROTOR_MAPPING:
      cerr << " has rotor mapping that is invalid." << endl;
      return 7;
    case NO_ROTOR_STARTING_POSITION:
      cerr << " has no rotor starting position." << endl;
      return 8;
    case INVALID_REFLECTOR_MAPPING:
      cerr << " has invalid reflector mapping." << endl;
      return 9;
    case INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS:
      cerr << " has incorrect number of reflector parameters." <<endl;
      return 10;
    case ERROR_OPENING_CONFIGURATION_FILE:
      cerr << " The input file cannot be opened correctly." << endl;
      return 11;
    default: cerr << "Unknown error." << endl;     
    }
  }
  return 0;
}
