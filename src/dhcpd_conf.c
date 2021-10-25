/**
 * @file dhcpd_conf.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief config the dhcp server with user data.
 * @version 0.2.2
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
initMem (struct  variable *data)
{
  MALLOC_AND_ERRCHECK (data->tmp, sizeof (char));

  MALLOC_AND_ERRCHECK (data->subnet, sizeof (char));

  MALLOC_AND_ERRCHECK (data->netmask, sizeof (char));

// MALLOC_AND_ERRCHECK (data->rangeUp, sizeof (char));

// MALLOC_AND_ERRCHECK (data->rangeDown, sizeof (char));

  MALLOC_AND_ERRCHECK (data->gateway, sizeof (char));

  MALLOC_AND_ERRCHECK (data->dns, sizeof (char));

  MALLOC_AND_ERRCHECK (data->configLoc, sizeof (char));
}

void
getData (int argc, char *argv[], struct variable *data)
{
  switch ((unsigned long int)argv[0])
  {
  case 'network':
    strcpy (data->subnet, argv[2]);
    strcpy (data->netmask, argv[3]);
    break;

  case 'default-router':
    strcpy (data->gateway, argv[2]);
    break;

  case 'dns-server':
    strcpy (data->dns, argv[2]);
    //TODO do we need second dns?
    break;

  default:
    break;
  }

}

void
setData (struct variable *data)
{
  strcpy (data->tmp, "subnet ");
  strcpy (data->tmp, data->subnet);
  strcpy (data->tmp, " netmask ");
  strcpy (data->tmp, data->netmask);
  strcpy (data->tmp, " { \n");

  strcpy (data->tmp, "option routers ");
  strcpy (data->tmp, data->gateway);
  strcpy (data->tmp, "; \n");


  strcpy (data->tmp, "option domain-name-servers ");
  strcpy (data->tmp, data->dns);
  strcpy (data->tmp, "; } \n");
}

void
pushData (struct variable *data)
{
  fputs (data->tmp, data->dhcpdconfig);
}

void
initfile (struct variable *data)
{
  strcpy (data->configLoc, "/etc/dhcp/dhcpd.conf");

  data->dhcpdconfig = fopen (data->configLoc, "w");
}

/*
void
getRange (int argc, char *argv[], struct variable *data)
{
  strcpy (data->range, "range ");
  strcpy (data->range, argv[0]);

  strcpy (data->range, " ");

  strcpy (data->range, argv[1]);
  strcpy (data->range, ";");

  fputs (data->range, data->dhcpdconfig);
}
*/

void
freeMem (struct  variable *data)
{
  free (data->tmp);
  free (data->subnet);
  free (data->netmask);
  //free (data->rangeUp);
  //  free (data->rangeDown);
  free (data->gateway);
  free (data->dns);
  free (data->configLoc);
}

void
closeFile (struct  variable *data)
{
  fclose (data->dhcpdconfig);
}
