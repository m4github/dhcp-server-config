/**
 * @file dhcpd_conf.h
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief  A library to config the dhcp server with user data.
 * @version 0.3.2
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

#define ARGC_COUNT_ERROR(arg)  \
 if(arg < 4 ) \
  { \
    fprintf(stderr, "Add more arguments\n"); \
    exit(EXIT_FAILURE); \
  } \


struct pool
{
  char *subnet;

  char *netmask;

  char *rangeUp;

  char *rangeDown;

  char *gateway;

  char *dns;
};

void getData (int argc, char *argv[], struct pool *data);

void initData (struct pool *data);

void writeConfigFile (struct pool *data);

void writeBackUpFile (struct pool *data);

void initMem (struct pool *data);

void freeMem (struct pool *data);

#endif