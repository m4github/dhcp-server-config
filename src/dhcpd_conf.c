/**
 * @file dhcpd_conf.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief config the dhcp server with user data.
 * @version 0.2.4
 * @date 23 Oct 2021
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  
#include "dhcpd_conf.h"

#define MAX_LEN 1024

void
initMem (struct  pool *data)
{
  MALLOC_AND_ERRCHECK (data->tmp, sizeof (char));

  MALLOC_AND_ERRCHECK (data->subnet, sizeof (char));

  MALLOC_AND_ERRCHECK (data->netmask, sizeof (char));

// MALLOC_AND_ERRCHECK (data->rangeUp, sizeof (char));

// MALLOC_AND_ERRCHECK (data->rangeDown, sizeof (char));

  MALLOC_AND_ERRCHECK (data->gateway, sizeof (char));

  MALLOC_AND_ERRCHECK (data->dns, sizeof (char));
}

void
getData (int argc, char *argv[], struct pool *data)
{
  if (!strcmp (argv[1], "network") )
  {
    strcat (data->subnet, argv[2]);
    strcat (data->netmask, argv[3]);
  }

  if (!strcmp (argv[1], "default-router") )
    strcat (data->gateway, argv[2]);

  if (!strcmp (argv[1], "dns-server") )
  {
    strcat (data->dns, argv[2]);
    //TODO do we need second dns?
  }
}

void
setData (struct pool *data)
{
  sprintf (data->tmp, "subnet ");
  strcat (data->tmp, data->subnet);
  strcat (data->tmp, " netmask ");
  strcat (data->tmp, data->netmask);
  strcat (data->tmp, " { \n");

  strcat (data->tmp, "option routers ");
  strcat (data->tmp, data->gateway);
  strcat (data->tmp, "; \n");

  strcat (data->tmp, "option domain-name-servers ");
  strcat (data->tmp, data->dns);
  strcat (data->tmp, "; } \n");
}

void
pushData (struct pool *data)
{
  FILE *dhcpdconfig = fopen ("/etc/dhcp/dhcpd.conf", "w");

  if (dhcpdconfig == NULL)
    exit (EXIT_FAILURE);

  fputs (data->tmp, dhcpdconfig);

  fclose (dhcpdconfig);
}

void
freeMem (struct  pool *data)
{
  free (data->tmp);
  free (data->subnet);
  free (data->netmask);
  //free (data->rangeUp);
  //free (data->rangeDown);
  free (data->gateway);
  free (data->dns);
}
