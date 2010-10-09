/*
 * File: libgps.h
 * Author: Mark Ross
 * Creation Date: 11.09.2010
 * Description: This is a modified version of libgps for use on a uC. This library 
 * only cares about the GGA sentence, because it gives latitude, longitude and 
 * elevation. This library expects that the GPS data does not stop streaming in
 * because it sits and waits for the next GPGGA sentence.
 */

#ifndef LIBGPS_ARDUINO_H
#define LIBGPS_ARDUINO_H


//#include <Messenger.h> // this needs to be in the main .pde
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "WProgram.h" // Serial support
#include "util.h"
#include "debug_stuff.h"

#define SUCCESS 0
#define FAILURE -1

/*
 * The max length of an NMEA sentence and some of the data sections contained within.
 */
#define GPS_MAX_SENTENCE_LENGTH 89

// Instantiate Messenger object with the default separator (the space character)
Messenger message = Messenger(); 

/*
 * gps_open() - attempts to open the device file given by fileName for the gpsdev_t given. Returns 0 if successful. If not, a negative number is returned and errno is set to indicate the error. See 'man fopen' for more help. This method also attempts to close the input stream that was previously being used by the gpsdev_t and can fail while doing that, too. See 'man fclose' for help with that. 
 */
void gps_init();

char *gps_get_gga();

void _NMEA_ready();

boolean receivedGPGGA = false;
// holds the current NMEA sentence
char tempSentenceBuff[GPS_MAX_SENTENCE_LENGTH + 1];

/******************************************************************/
/******************************************************************/

void gps_init() {  
  // Attach the callback function to the Messenger
  message.attach(_NMEA_ready);
}


char *gpgga = "$GPGGA";
  char nmeaType[7];  
  
// Messenger callback function
void _NMEA_ready() {
  // save the message to the buffer and print it
  Serial.print("PROCESSING MESSAGE...");
  message.copyString(tempSentenceBuff, GPS_MAX_SENTENCE_LENGTH + 1); 
  int i;
  for (i = 0; i < GPS_MAX_SENTENCE_LENGTH + 1; i++) {
    if (tempSentenceBuff[i] == '\r')
      tempSentenceBuff[i] = '\0';
    if (tempSentenceBuff[i] == '\n')
      tempSentenceBuff[i] = '\0';
  }
  Serial.println(tempSentenceBuff);
  
  // make sure the message is a GPGGA sentence
  char *gpgga = "$GPGGA";
  char nmeaType[7];  
  for (i = 0; i < 6; i++) {
    nmeaType[i] = tempSentenceBuff[i];
  }
  nmeaType[6] = '\0';
 
  // if it is a GPGGA sentence, set the flag 
  if (strcmp(gpgga, nmeaType) == 0) {
    receivedGPGGA = true;
    Serial.println("GPGGA FOUND");
  } 
}

char *gps_get_gga() {
// clear the serial buffer
  Serial.flush();
  
  // wait for serial input and process it. exit when a GPGGA sentence is
  // received
  char c;
  while (!receivedGPGGA) {
    // wait for serial data to come in
    while (!Serial.available()) {
      delay(5);
    } 
    
    // get the next byte
    c = Serial.read();
    
    // make sure the byte is valid and process it
    if (isascii(c)) 
      message.process(c);
    
    // delay(5);
  } 
  
  // reset this flag
  receivedGPGGA = false;  
  
  return tempSentenceBuff; 
}

#endif /* LIBGPS_ARDUINO_H */

