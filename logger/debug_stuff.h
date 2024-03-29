/*******************************************************************

logger - Arduino GPS, acceleration, and temperature logging program
Copyright (C) 2010  Mark Ross and Steven Fan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************/

/*
 * File: debug_stuff.h
 * Author: Mark R.
 * Date: 11.08.2010
 * Description: Print debug messages to the serial port.
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
