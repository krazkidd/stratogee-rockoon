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
 * File: logger.pde
 * Author: Mark R.
 * Date: 11.08.2010
 * Description: This is a program; run on an AVR ATMega168 or similar 
 * Arduino-compatible microcontroller that logs GPS, accelerometer, and
 * temperature data. It works with any GPS that puts out NMEA sentences
 * over a TTL serial line, an ADXL345 accelo, and a DS18B20 temp. sensor.
 * It is possible to use this code without an Arduino board, but you will
 * need to find out how to program the AVR chip without it.
 */
 
#define DEBUG // comment this out to stop printing debug messages

#include <stdlib.h>
#include <string.h>
#include <Messenger.h> // for libgps
#include <Wire.h> // for libaccel
#include <OneWire.h> // for libtemp
#include "debug_stuff.h"
#include "libaccel_arduino.h"
#include "libopenlog_arduino.h"
#include "libgps_arduino.h"
#include "libtemp_arduino.h"

/* main power status LED */
boolean isLEDOn = false;
#define PIN_STATUS_LED 13

#define DELAY_LOOP 5

/* handle for the accelo */
acceldev_t accelDev;

/******************************************************************/
/******************************************************************/

/*
 * updateStatusLED() - this function runs about once a second due to the
 * GPS, so it justs flip the status LED on or off
 */
void updateStatusLED() {
  if (isLEDOn == true) {
    isLEDOn = false;
    digitalWrite(PIN_STATUS_LED, LOW);
  }
  else {
    isLEDOn = true;
    digitalWrite(PIN_STATUS_LED, HIGH);
  }
}

/*
 * setup() - this function is called by the Arduino bootloader to set
 * up the initial environment.
 */
void setup() {
  /* start serial interface */ 
  Serial.begin(4800);
  
  /* ready libgps (it needs to do one little thing) */
  gps_init();

  /* join I2C bus as a master device */
  Wire.begin(); 
 
  /* try to find the ADXL345 on the i2c bus */
  if (accel_open(&accelDev, 0x53) < 0) 
    // could not find accelo on i2c bus
    DEBUG_PRINT_ERROR("The ADXL345 could not be found on the i2c bus.");
  
  /* set status led pin as digital output */
  pinMode(PIN_STATUS_LED, OUTPUT);
}

/*
 * loop() - runs after setup() indefinitely
 */
void loop() {
  updateStatusLED();
  
  // update the GPS and log the GPGGA sentence
  openlog_write(gps_get_gga()); 
  
  /* update the accelo */
  accel_update(&accelDev);
  
  // log the accelo measurements
  openlog_write(accel_get_x(&accelDev));
  openlog_write(accel_get_y(&accelDev));
  openlog_write(accel_get_z(&accelDev));
  
  // log the temp.
  openlog_write(temp_get_temp());
  
  // write to the openlog
  openlog_flush();
  
  delay(DELAY_LOOP);
}


