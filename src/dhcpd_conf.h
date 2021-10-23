/**
 * @file dhcpd_conf.h
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief  A library to config the dhcp server with user data.
 * @version 0.2.0
 * @date 23 Oct 2021
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>

#if !defined(_DHCPD_CONF_H)
#define _DHCPD_CONF_H

#define MALLOC_AND_ERRCHECK(var, n)   var = (char *)malloc (sizeof (char) * MAX_LEN); \
 if(var == NULL && n > 0) \
  { \
    fprintf(stderr, "Couldn't allocate memory\n"); \
    exit(EXIT_FAILURE); \
  } \


struct variable
{
  char *network;

  char *range;

  char *gateway;

  char *dns;

  char *configLoc;

  FILE *dhcpdconfig;
};

void initfile (struct variable *data);

void initMem (struct variable *data);

void getNetwork (int argc, char *argv[], struct variable *data);

void getRange (int argc, char *argv[], struct variable *data);

void getGateway (int argc, char *argv[], struct variable *data);

void getDNS (int argc, char *argv[], struct variable *data);

void closeFile (struct variable *data);

void freeMem (struct variable *data);

#endif