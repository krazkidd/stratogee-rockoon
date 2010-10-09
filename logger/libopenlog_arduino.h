/*
 * File: libopenlog_arduino.h
 * Author: Mark R.
 * Date: 02.09.2010
 * Description: This library is used to communicate with SparkFun's
 * OpenLog. By default, it logs every byte that comes through the serial
 * line onto a Fat16 microSD card at 9600 BPS, 8n1 to a file. I'm not sure if
 * it creates a new file on every power up, though. See http://wiki.github.com/nseidle/OpenLog/
 * for more information.
 * 
 * It is possible to put the OpenLog into command mode in order to 
 * configure it and review the status of the microSD card. Initially,
 * this library is not intended to do anything in command mode since
 * all the data on the card can be read and modified on a desktop computer.
 * There may be one exception: the 'init' command is meant to re-initialize
 * the card if there are any problems. But I don't know how likely this is to happen.
 */

#ifndef LIBOPENLOG_ARDUINO_H
#define LIBOPENLOG_ARDUINO_H

#include <string.h>
#include "debug_stuff.h"
#include "util.h"
#include "WProgram.h" // for Serial support

#define BUFFER_SIZE 256 // the maximum size the data can be before flushing is required

#define SUCCESS 0 
#define FAILURE -1

char buffer[BUFFER_SIZE + 1];// = "\0"; /* buffer to hold data before flushing to openlog */

int dataEnd = -1;  // the index of the last character in the buffer (if -1, then the buffer is empty)

/*
 * openlog_write() - writes data to the openlog buffer. This function is overloaded so that you
 * don't have to worry about converting anything.
 */
int openlog_write(char *str) {
  //DEBUG_PRINT("Writing STRING to openlog buffer: ");
  //DEBUG_PRINT_LN(str);
  
  //if (dataEnd == -1)
  //  buffer[0] = '\0';
  
  int origBufferSize;
  origBufferSize = strlen(buffer);
  
  // add a space delimiter
  if (origBufferSize != 0)
    strncat(buffer, " ", BUFFER_SIZE - origBufferSize);
  
  // write as many chars as possible to the buffer. str must be null-terminated
  strncat(buffer, str, BUFFER_SIZE - (origBufferSize + 1));
  
  // let the caller know if the entirety of str was written to the buffer
  if (strlen(str) + 1 /* a space was added */ > BUFFER_SIZE - origBufferSize)
    return FAILURE;
    
  return SUCCESS;
}

int openlog_write(float fl) {
  //char tempBuff[10];
// fmtDouble(4.44, 2, tempBuff, 10);
// Serial.println(tempBuff);
 

 // DEBUG_PRINT("Writing '")
 // DEBUG_PRINT(fl);
 // DEBUG_PRINT("' to openlog buffer...")
  
 // if (dataEnd == -1)
  //  buffer[0] = '\0';  

  int origBufferSize;
  origBufferSize = strlen(buffer);
 // DEBUG_PRINT("Original buffer size = ")
 // DEBUG_PRINT(origBufferSize)  
 // DEBUG_PRINT_LN("...")
  
  // add a space delimiter
  if (origBufferSize != 0)
    strncat(buffer, " ", BUFFER_SIZE - origBufferSize);
  
  // convert the float argument to string
 // char tempBuffer[BUFFER_SIZE + 1];
  char tempBuff[16];
  
  //tempBuffer[0] ='\0';
  //sprintf(tempBuffer, "%f", fl);
  fmtDouble(fl, 6, tempBuff, 16);
 // DEBUG_PRINT("String version of float: ")
 // DEBUG_PRINT_LN(tempBuff)  
  
  // concatenate to the buffer
  strncat(buffer, tempBuff, BUFFER_SIZE - (origBufferSize + 1));
 // DEBUG_PRINT_LN("Final state of buffer: ");
 // DEBUG_PRINT_LN(buffer);
  
  // let the caller know if the entirety of str was written to the buffer
  if (strlen(tempBuff) + 1 /* a space was added */ > BUFFER_SIZE - origBufferSize) {
    DEBUG_PRINT_ERROR("OpenLog buffer overflow.");
    return FAILURE;
  }
    
  return SUCCESS;
}

int openlog_write(int num) {
  //DEBUG_PRINT_LN("Writing INT to openlog buffer.");
 // if (dataEnd == -1)
 //   buffer[0] = '\0';
  
  int origBufferSize;
  origBufferSize = strlen(buffer);
  
  // add a space delimiter
  if (origBufferSize != 0)
    strncat(buffer, " ", BUFFER_SIZE - origBufferSize);
  
  // convert the float argument to string
  char tempBuffer[BUFFER_SIZE + 1];
  tempBuffer[0] ='\0';
  sprintf(tempBuffer, "%d", num);
  
  // concatenate to the buffer
  strncat(buffer, tempBuffer, BUFFER_SIZE - (origBufferSize + 1));
  
  // let the caller know if the entirety of str was written to the buffer
  if (strlen(tempBuffer) + 1 /* a space was added */ > BUFFER_SIZE - origBufferSize)
    return FAILURE;
    
  return SUCCESS;
}

/*
 * openlog_flush() - this function actually writes data to the serial line
 * in order to be stored on the openlog. There was no real reason for doing
 * it this way other than to make the openlog_write() functions smaller.
 */
int openlog_flush() {
  //DEBUG_PRINT("Writing to OpenLog: ");
 // DEBUG_PRINT_LN(buffer);
  
  // write the data to the openlog
  Serial.println(buffer); 
   
  // clear the buffer
  buffer[0] = '\0';
  
  return SUCCESS;
}

#endif /* LIBOPENLOG_ARDUINO_H */
