/* File: status.h
 * Author: Asif Shahidullah
 * Date: 2010-09-11
 * Description: Verifies the status of the different devices  */

#ifndef _STATUS_H
#define _STATUS_H

/* Checks the status of the radio using the thunder/flash sequence */
int STATUS_radio_check();
/* Checks the status of the accelerometer by attempting to update the data */
int STATUS_accelerometer_check();
/* Checks the status of the two GPS units by retrieving NMEA sentences from them */
int STATUS_gps_check();

#endif /* _STATUS_H */
