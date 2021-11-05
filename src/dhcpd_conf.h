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

#define MAX_LEN 15

#if !defined(_DHCPD_CONF_H)
#define _DHCPD_CONF_H

#define ARGUMENT_ALLERT \
fprintf(stderr, "Add more arguments\n"); \
    exit(EXIT_FAILURE); \

#define ARGC_4COUNT_ERROR(arg)  \
 if(arg < 4 ) \
  { \
   ARGUMENT_ALLERT; \
  } \

#define ARGC_3COUNT_ERROR(arg)  \
 if(arg < 3 ) \
  { \
       ARGUMENT_ALLERT; \
  } \

struct pool
{
  char subnet[MAX_LEN];
  char netmask[MAX_LEN];
  char rangeUp[MAX_LEN];
  char rangeDown[MAX_LEN];
  char gateway[MAX_LEN];
  char dns[MAX_LEN];
};

void get_data (int argc, char *argv[], struct pool *data);
void init_data (struct pool *data);
void write_config_file (struct pool *data);
void write_backup_file (struct pool *data);

#endif