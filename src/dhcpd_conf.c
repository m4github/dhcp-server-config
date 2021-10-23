/**
 * @file dhcpd_conf.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief config the dhcp server with user data.
 * @version 0.2.0
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
  MALLOC_AND_ERRCHECK (data->network, sizeof (char));

  MALLOC_AND_ERRCHECK (data->range, sizeof (char));

  MALLOC_AND_ERRCHECK (data->gateway, sizeof (char));

  MALLOC_AND_ERRCHECK (data->dns, sizeof (char));

  MALLOC_AND_ERRCHECK (data->configLoc, sizeof (char));
}

void
initfile (struct variable *data)
{
  sprintf (data->configLoc, "/etc/dhcp/dhcpd.conf");

  data->dhcpdconfig = fopen (data->configLoc, "w");
}

void
getNetwork (int argc, char *argv[],struct variable *data)
{
//subnet and  netmask

  sprintf (data->network, "subnet ");
  sprintf (data->network, argv[0]);

  sprintf (data->network, " netmask ");
  sprintf (data->network, argv[1]);

  sprintf (data->network, " { ");

  fputs (data->network, data->dhcpdconfig);
}

void
getRange (int argc, char *argv[],struct variable *data)
{
  sprintf (data->range, "range ");
  sprintf (data->range, argv[0]);

  sprintf (data->range, " ");

  sprintf (data->range, argv[1]);
  sprintf (data->range, ";");

  fputs (data->range, data->dhcpdconfig);
}

void
getGateway (int argc, char *argv[],struct variable *data)
{
  sprintf (data->gateway, "option routers ");
  sprintf (data->gateway, argv[0]);
  sprintf (data->gateway, ";");

  fputs (data->gateway, data->dhcpdconfig);
}

void
getDNS (int argc, char *argv[],struct variable *data)
{
  sprintf (data->dns, "option domain-name-servers ");
  sprintf (data->dns, argv[0]);
  sprintf (data->dns, ";");

  sprintf (data->dns, " }");

  fputs (data->dns, data->dhcpdconfig);
}

void
freeMem (struct  variable *data)
{
  free (data->network);
  free (data->range);
  free (data->gateway);
  free (data->dns);
  free (data->configLoc);
}

void
closeFile (struct  variable *data)
{
  fclose (data->dhcpdconfig);
}