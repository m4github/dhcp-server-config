/**
 * @file dhcpd_conf.h
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief  A library to config the dhcp server with user data.
 * @version 0.1.1
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
  char *subnet;
  char *netmask;
  char *rangeUp;
  char *rangeDown;
  char *gateway;
  char *dns;

  char *configLoc;

  FILE *dhcpdConfig;

};

void getSubnet (struct variable *data);

void getnetMask (struct variable *data);

void getRange (struct variable *data);

void getGateway (struct variable *data);

void getDNS (struct variable *data);

void initMem (struct variable *data);

void setLoc (struct variable *data);

void closeFile (struct variable *data);

void freeMem (struct variable *data);

#endif
