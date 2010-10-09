/*
 * File: debug_stuff.h
 * Author: Mark R.
 * Date: 11.08.2010
 * Description: This header is necessary because the Arduino IDE fucks
 * with the source files before compiling.
 */ 
 
#ifndef DEBUG_STUFF_H
#define DEBUG_STUFF_H

#include "WProgram.h" // for Serial support

#ifdef DEBUG
  #define DEBUG_PRINT(...) Serial.print(__VA_ARGS__);
  #define DEBUG_PRINT_LN(...) Serial.println(__VA_ARGS__);
  int xzxzxz; // counter used for DEBUG_PRINT_ERROR
  #define DEBUG_PRINT_ERROR(...) for (xzxzxz = 0; xzxzxz < 25; xzxzxz++) { Serial.print("ERROR: "); Serial.println(__VA_ARGS__); } // TODO change this when GPS is added
#else
  // these are left blank on purpose!
  #define DEBUG_PRINT(...) 
  #define DEBUG_PRINT_LN(...)
  #define DEBUG_PRINT_ERROR(...)
#endif

#endif /* DEBUG_STUFF_H */
