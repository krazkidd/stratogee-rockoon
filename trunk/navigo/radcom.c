#include "radcom.h"
#include <stdio.h>

/* NOTE: To preserve system resources, we decided not to include
 * a string length saftey check. Or, we could edit paclen in 
 * axports too. */
void beacon(char *message)
{
  char I_sysCommand[256];
  sprintf(I_sysCommand, "beacon -c %s -d %s -s sbc-ax \"%s\"", 
    BALLOON_CALLSIGN, CONTROL_STATION_CALLSIGN, message);
  system(I_sysCommand);
}

char * get_radio()
{
  char buff[BUFF_SIZE];
  FILE *packet_file = fopen(APRS_PACKETS_FILE, "r");
  fgets(buff, BUFF_SIZE, packet_file);
  printf("%s\n", buff);
  fclose(packet_file);
  return NULL;
}

int main(void)
{
  get_radio();
}

