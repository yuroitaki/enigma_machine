/* Header file "errors.h" */

/* used in C++2 Assessed Exercise */

#ifndef ERRORS_H
#define ERRORS_H

/* error codes  */
#define INSUFFICIENT_NUMBER_OF_PARAMETERS		1
#define INVALID_INPUT_CHARACTER				2
#define INVALID_INDEX					3
#define NON_NUMERIC_CHARACTER				4
#define IMPOSSIBLE_PLUGBOARD_CONFIGURATION		5
#define INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS	6
#define INVALID_ROTOR_MAPPING				7
#define NO_ROTOR_STARTING_POSITION			8
#define INVALID_REFLECTOR_MAPPING			9
#define INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS	10
#define ERROR_OPENING_CONFIGURATION_FILE		11
#define NO_ERROR					0

/* global constant */
#define CONVERSION  65

/* signal codes*/
#define PB 100
#define RF 200
#define RP 300
#define FORWARD 1000
#define BACKWARD 2000
#define SETUP -1
#define RUN -2

#endif
