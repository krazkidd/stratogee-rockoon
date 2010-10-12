#ifndef _RADCOM_H
#define _RADCOM_H	1

#define CONTROL_STATION_CALLSIGN "KF7IYK-0"
#define BALLOON_CALLSIGN "KF7IYK-2"
#define APRS_PACKETS_FILE "/tmp/Packets"
#define BUFF_SIZE 1024

/* Sends a message to axport using a system call */
void beacon(char *);

/* retrieves the first entry in the /tmp/Packets file */
char * get_packet();

#endif /* _RADCOM_H */
