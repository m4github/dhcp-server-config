/**
 * @file dhcpd_conf.h
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief  A library to config the dhcp server with user data.
 * @version 0.2.2
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
  char *tmp;

  char *subnet;

  char *netmask;

// char *rangeUp;

  //char *rangeDown;

  char *gateway;

  char *dns;

  char *configLoc;

  FILE *dhcpdconfig;
};

void getData (int argc, char *argv[], struct variable *data);

void setData (struct variable *data);

void pushData (struct variable *data);

void initfile (struct variable *data);

void initMem (struct variable *data);

//void getRange (int argc, char *argv[], struct variable *data);

void closeFile (struct variable *data);

void freeMem (struct variable *data);

#endif