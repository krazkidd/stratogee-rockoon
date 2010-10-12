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
 * File: libtemp_arduino.h
 * Author: Mark Ross
 * Description: Uses a DIO pin on the AVR chip as a 1-Wire master to get
 * temperature measurements from a DS18B20.
 */

//#include <OneWire.h> // include this in the main .pde
#include "debug_stuff.h"

#define DS18B20_FAMILY_CODE 0x28
#define DS18B20_FUNC_CONVERT 0x44
#define DS18B20_FUNC_READ_SCRATCHPAD 0xBE

// DS18B20 Temperature chip i/o
OneWire ds(10);  // on pin 10

byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];

float temp_get_temp() {
  // on each iteration of loop(), scan for the next device. When there are none left,
  // reset so that the next loop() iteration starts at the first device again
 // if ( !ds.search(addr)) {
   //   Serial.print("No more addresses.\n");
     // ds.reset_search();
      //return 9999.99;
  //}

  // print the 64-bit hex address of the current device
  /*Serial.print("R=");
  for( i = 0; i < 8; i++) {
    Serial.print(addr[i], HEX);
    Serial.print(" ");
  }*/

  // match the CRC value of the first 7 bytes of the address with the MSB
  /*if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.print("CRC is not valid!\n");
      return 9999.99;
  }*/

  // make sure we're talking to a DS18B20
  /*if ( addr[0] != DS18B20_FAMILY_CODE) {
      Serial.print("Device is not a DS18B20 family device.\n");
      return 9999.99;
  }*/

  // "reset" the 1-Wire bus, address the current device, and send the convert command
  ds.reset();
 // ds.select(addr);
 ds.skip();
  ds.write(DS18B20_FUNC_CONVERT,1);         // start conversion, with parasite power on at the end

  // wait for the DS18B20 because it is using parasite power
  delay(850);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  // "reset" the 1-Wire bus, address the current device, and send Read Scratchpad command
  present = ds.reset();
  //ds.select(addr);
  ds.skip();  
  ds.write(DS18B20_FUNC_READ_SCRATCHPAD);       

  // print the presence of the current device 
  //Serial.print("P=");
  //Serial.print(present,HEX);
  // read and print the scratchpad
  //Serial.print(" ");
  //Serial.println();
  //Serial.println("SCRATCHPAD:");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    //Serial.print(data[i], HEX);
    //Serial.print(" ");
  }
  // calculate and print the crc value of the scratchpad
  //Serial.print(" CRC=");
  int dataCRC;
  dataCRC = OneWire::crc8(data, 8);
  //Serial.print( dataCRC = OneWire::crc8( data, 8), HEX);
  //Serial.print(" ");
  
  // check the calculated crc with the crc of the scratchpad in the 9th byte of the read data
  if ( dataCRC != data[8]) {
      //Serial.print("CRC of data is not valid!\n");
      return 9999.99;
  }

  // print the decimal temperature
  int16_t temp;
  temp = data[1];
  temp = temp << 8;
  temp = temp | data[0];
  float convertedTemp;
  convertedTemp = temp * 0.0625;
  //Serial.print("Temp: ");
  //Serial.print(convertedTemp);
  //Serial.print(" degrees C");
  
  //Serial.println();
  //delay(250); 
  
  return convertedTemp;
}
