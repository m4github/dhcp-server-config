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
  switch ((unsigned long int)argv[0]) //TODO is it secure?
  {
  case 'network':
    sprintf (data->subnet, argv[1]);
    sprintf (data->netmask, argv[2]);
    break;

  case 'default-router':
    sprintf (data->gateway, argv[1]);
    break;

  case 'dns-server':
    sprintf (data->dns, argv[1]);
    //TODO do we need second dns?
    break;

  default:
    break;
  }

}

void
setData (struct variable *data)
{
  sprintf (data->tmp, "subnet ");
  sprintf (data->tmp, data->subnet);
  sprintf (data->tmp, " netmask ");
  sprintf (data->tmp, data->netmask);
  sprintf (data->tmp, " { \n");

  sprintf (data->tmp, "option routers ");
  sprintf (data->tmp, data->gateway);
  sprintf (data->tmp, "; \n");


  sprintf (data->tmp, "option domain-name-servers ");
  sprintf (data->tmp, data->dns);
  sprintf (data->tmp, "; } \n");
}

void
pushData (struct variable *data)
{
  fputs (data->tmp, data->dhcpdconfig);
}

void
initfile (struct variable *data)
{
  sprintf (data->configLoc, "/etc/dhcp/dhcpd.conf");

  data->dhcpdconfig = fopen (data->configLoc, "w");
}

/*
void
getRange (int argc, char *argv[], struct variable *data)
{
  sprintf (data->range, "range ");
  sprintf (data->range, argv[0]);

  sprintf (data->range, " ");

  sprintf (data->range, argv[1]);
  sprintf (data->range, ";");

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