/**
 * @file dhcpd_conf.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief config the dhcp server with user data.
 * @version 0.6.5
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

  if (argc && !strcmp (argv[1], "-reset"))
  {
    fclose (fopen ("/etc/dhcp/dhcpd.conf", "w"));
    exit (EXIT_FAILURE);
  }
  if (argc == 4 && !strcmp (argv[1], "network"))
  {
    ARGC_COUNT_ERROR (argc);

    sprintf (data->subnet, argv[2], sizeof (char));
    sprintf (data->netmask, argv[3], sizeof (char));
  }

  if (argc == 3  && !strcmp (argv[1], "default-router"))
    sprintf (data->gateway, argv[2], sizeof (char));

  if (argc == 3  && !strcmp (argv[1], "dns-server"))
    sprintf (data->dns, argv[2], sizeof (char));
}

void
initData (struct pool *data)
{
  char *val = MALLOC_AND_ERRCHECK (val, sizeof (char));

  FILE *configInfo = fopen ("/etc/dhcp/config_info.txt", "r");

  if (configInfo == NULL)
    exit (EXIT_FAILURE);

  fscanf (configInfo, "%s", val);
  sprintf (data->subnet, val);

  fscanf (configInfo,  "%s", val);
  sprintf (data->netmask, val);

  fscanf (configInfo,  "%s", val);
  sprintf (data->gateway, val);

  fscanf (configInfo,  "%s", val);
  sprintf (data->dns, val);


  fclose (configInfo);

  free (val);
}

void
writeConfigFile (struct pool *data)
{
  char *tmp;
  MALLOC_AND_ERRCHECK (tmp, sizeof (char));

  FILE *dhcpdconfig = fopen ("/etc/dhcp/dhcpd.conf", "w");

  if (dhcpdconfig == NULL)
    exit (EXIT_FAILURE);

  sprintf (tmp, "subnet ");
  strcat (tmp, data->subnet);
  strcat (tmp, " netmask ");
  strcat (tmp, data->netmask);
  strcat (tmp, " { \n");

  strcat (tmp, "option routers ");
  strcat (tmp, data->gateway);
  strcat (tmp, "; \n");

  strcat (tmp, "option domain-name-servers ");
  strcat (tmp, data->dns);
  strcat (tmp, "; } \n");

  fputs (tmp, dhcpdconfig);

  fclose (dhcpdconfig);

  free (tmp);

}

void
writeBackUpFile (struct pool *data)
{
  char *tmp;
  MALLOC_AND_ERRCHECK (tmp, sizeof (char));

  FILE *configInfo = fopen ("/etc/dhcp/config_info.txt", "w");

  if (configInfo == NULL)
    exit (EXIT_FAILURE);

  sprintf (tmp, data->subnet);
  strcat (tmp, "  \n");

  strcat (tmp, data->netmask);
  strcat (tmp, "  \n");

  strcat (tmp, data->gateway);
  strcat (tmp, " \n");

  strcat (tmp, data->dns);
  strcat (tmp, " \n");

  fputs (tmp, configInfo);

  fclose (configInfo);

  free (tmp);
}

void
freeMem (struct  pool *data)
{
  free (data->subnet);
  free (data->netmask);
  //free (data->rangeUp);
  //free (data->rangeDown);
  free (data->gateway);
  free (data->dns);
}
