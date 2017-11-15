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
    Config confg(argc,argv,"output.txt");
    Plugboard_Reflector pb_ref(&confg);
    Enigma enigma_machine(&confg,&pb_ref); 
    enigma_machine.encrypt();
  }
 

 catch(int code){
   switch(code){
   case INSUFFICIENT_NUMBER_OF_PARAMETERS:
     cerr <<  "There is an insufficient number of parameters from the input configuration files." << endl;
     break;
   case INVALID_INPUT_CHARACTER:
     cerr << " has invalid input character." << endl;
     break;
   case INVALID_INDEX:
     cerr << " has invalid index." << endl;
     break;
   case NON_NUMERIC_CHARACTER:
     cerr << " has non-numeric character." << endl;
     break;
   case IMPOSSIBLE_PLUGBOARD_CONFIGURATION:
     cerr << " has impossible plugboard configuration." <<endl;
     break;
   case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS:
     cerr << " has incorrect number of plugboard parameters."<<endl;
     break;
   case INVALID_ROTOR_MAPPING:
     cerr << " has rotor mapping that is invalid." << endl;
     break;
   case NO_ROTOR_STARTING_POSITION:
     cerr << " has no rotor starting position." << endl;
     break;
   case INVALID_REFLECTOR_MAPPING:
     cerr << " has invalid reflector mapping." << endl;
     break;
   case INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS:
     cerr << " has incorrect number of reflector parameters." <<endl;
     break;
   case ERROR_OPENING_CONFIGURATION_FILE:
     cerr << " cannot be opened correctly." << endl;
     break;
   default: cerr << "Unknown error." << endl;     
   }
 }
  return 0;
}
