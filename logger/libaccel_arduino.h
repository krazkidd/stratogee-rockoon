/*
 * File: libaccel_arduino.h
 * Author: Mark R.
 * Date: 09.09.2010
 * Description: This is a modified version of libaccel for use on an Arduino uC.
 * The code for retrieving the measurement from the accelo was provided by Euristic at:
 * http://codeyoung.blogspot.com/2009/11/adxl345-accelerometer-breakout-board.html
 */

#ifndef LIBACCEL_ARDUINO_H
#define LIBACCEL_ARDUINO_H

#include <stdint.h>
//#include <Wire.h> // this needs to be in the main .pde
#include "debug_stuff.h"

/*
 * These are register names if REG is in the name. If VAL is in the name, the
 * value corresponds to what one would expect to read or write to the particular
 * register.
 */
#define ADXL345_REG_DEVID 0x00
#define ADXL345_VAL_DEVID 0xe5
#define ADXL345_REG_DATAX0 0x32
#define ADXL345_REG_DATAX1 0x33
#define ADXL345_REG_DATAY0 0x34
#define ADXL345_REG_DATAY1 0x35
#define ADXL345_REG_DATAZ0 0x36
#define ADXL345_REG_DATAZ1 0x37
#define ADXL345_REG_POWERCTL 0x2d
#define ADXL345_VAL_MEASURE 0x08

/*
 * The default scale factor.
 */
#define ADXL345_SCALE_FACTOR 0.0039

#define SUCCESS 0
#define FAILURE -1

typedef struct {
  /*
   * the accelerometer's I2C address
   */
  int accelAddr;

  int16_t xMeasurement;
  int16_t yMeasurement;
  int16_t zMeasurement;
} acceldev_t;

int accel_open(acceldev_t *accelDev, int accelAddr);
int accel_close(acceldev_t *accelDev);
int accel_update(acceldev_t *accelDev);
float accel_get_x(acceldev_t *accelDev);
float accel_get_y(acceldev_t *accelDev);
float accel_get_z(acceldev_t *accelDev);
/*
 * accel_get_magnitude() - returns a float describing the total g-force in the direction of acceleration. It is calculated by square-rooting the sum of the squares of each component.
 */
float accel_get_magnitude(acceldev_t *accelDev);
/*
 * _ADXL345_write() - an internal function for writing to the ADXL345 using
 * Arduino's Wire library. devAddr is the i2c address of the accelo, register23 is
 * the register being written to, and value is the value to write.
 */
int _ADXL345_write(int devAddr, byte register23, byte value);
/*
 * _ADXL345_read() - an internal function for reading from the ADXL345 using
 * Arduino's Wire library. devAddr is the i2c address of the accelo, register23 is
 * the first register being read from, numBytes is the number of bytes to be read
 * sequentially including register23, and data is the array where the returned values
 * are to be saved.
 */
int _ADXL345_read(int devAddr, byte register23, int numBytes, byte *data);

int _ADXL345_detect(acceldev_t *accelDev) {
  /* read register 0x00 to get the ADXL345's device id, which is 0xe5. This is not the same as the i2c address and basically just serves the purpose of making sure an ADXL345 is at an i2c address. */
  int ret;
  byte data;
  ret = _ADXL345_read(accelDev->accelAddr, ADXL345_REG_DEVID, 1, &data);

  if (data != ADXL345_VAL_DEVID) {
    DEBUG_PRINT_ERROR("ADXL345 NOT DETECTED")
    
    DEBUG_PRINT("The devID returned by register ");
    DEBUG_PRINT(ADXL345_REG_DEVID, HEX);
    DEBUG_PRINT(" at i2c address ");
    DEBUG_PRINT(accelDev->accelAddr, HEX);
    DEBUG_PRINT(" was ");
    DEBUG_PRINT(data, HEX);
    DEBUG_PRINT(ADXL345_VAL_DEVID, HEX);
    DEBUG_PRINT_LN(".");
    
    return FAILURE;
  }

  //DEBUG_PRINT_LN("ADXL345 DETECTED")

  return SUCCESS;
}

int _ADXL345_measuremode(acceldev_t *accelDev) {
  // TODO get the current value in the POWERCTL register (if it is used for anything else)
  int ret;
  ret = _ADXL345_write(accelDev->accelAddr, ADXL345_REG_POWERCTL, ADXL345_VAL_MEASURE);

  return SUCCESS;
}

int _ADXL345_standbymode(acceldev_t *accelDev) {
  // TODO get the current value in the POWERCTL register (if it is used for anything else)
  int ret;
  ret = _ADXL345_write(accelDev->accelAddr, ADXL345_REG_POWERCTL, 0x00);

  return SUCCESS;
}

int _ADXL345_write(int devAddr, byte register23, byte value) {
  Wire.beginTransmission(devAddr);
  Wire.send(register23);
  Wire.send(value);
  Wire.endTransmission();

  return SUCCESS;
}

int _ADXL345_read(int devAddr, byte register23, int numBytes, byte *data) {
  Wire.beginTransmission(devAddr);
  Wire.send(register23);
  Wire.endTransmission();

  Wire.beginTransmission(devAddr);
  Wire.requestFrom(devAddr, numBytes);
 /* int i;
  for(i = 0; i < numBytes && Wire.available(); i++) {
    data[i] = Wire.receive();
  }*/
  int i = 0;
  while(Wire.available())    //device may send less than requested (abnormal)
  { 
    data[i] = Wire.receive(); // receive a byte
    i++;
  }
  Wire.endTransmission();

  return FAILURE;
}

int accel_open(acceldev_t *accelDev, int accelAddr) {
  accelDev->accelAddr = accelAddr;

  /* try to detect the accelerometer */
  int ret = _ADXL345_detect(accelDev);
  
  // put the accelo in measure mode
  if (ret == SUCCESS)
    _ADXL345_measuremode(accelDev);
    
  return ret;
}

int accel_close(acceldev_t *accelDev) {
  /* Nothing needs to be done here for the Arduino. */

  return SUCCESS; 
}

int accel_update(acceldev_t *accelDev) {
  byte data[6]; /* this will hold the measurements for X, Y, and Z - 2 bytes each */

//  _ADXL345_measuremode(accelDev);

  /* read 6 bytes from the I2C bus starting at DATAX0 */
  int ret;
  ret = _ADXL345_read(accelDev->accelAddr, ADXL345_REG_DATAX0, 6, data); 

  /* now put the measurements in accelDev correctly */
  accelDev->xMeasurement = 0x00;
  accelDev->xMeasurement = data[1];
  accelDev->xMeasurement = accelDev->xMeasurement << 8;
  accelDev->xMeasurement |= data[0];

  accelDev->yMeasurement =  0x00;
  accelDev->yMeasurement = data[3];
  accelDev->yMeasurement = accelDev->yMeasurement << 8;
  accelDev->yMeasurement |= data[2];

  accelDev->zMeasurement = 0x00;
  accelDev->zMeasurement = data[5];
  accelDev->zMeasurement = accelDev->zMeasurement << 8;
  accelDev->zMeasurement |= data[4];

  //_ADXL345_standbymode(accelDev);

  return SUCCESS;
}

float accel_get_x(acceldev_t *accelDev) {
  return accelDev->xMeasurement * ADXL345_SCALE_FACTOR;
}

float accel_get_y(acceldev_t *accelDev) {
  return accelDev->yMeasurement * ADXL345_SCALE_FACTOR;
}

float accel_get_z(acceldev_t *accelDev) {
  return accelDev->zMeasurement * ADXL345_SCALE_FACTOR;
}



#endif /* LIBACCEL_ARDUINO_H */


