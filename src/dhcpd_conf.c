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

  MALLOC_AND_ERRCHECK (data->rangeUp, sizeof (char));

  MALLOC_AND_ERRCHECK (data->rangeDown, sizeof (char));

  MALLOC_AND_ERRCHECK (data->gateway, sizeof (char));

  MALLOC_AND_ERRCHECK (data->dns, sizeof (char));
}

void
getData (int argc, char *argv[], struct pool *data)
{
  if (argc && !strcmp (argv[1], "-reset"))
    {
      fclose (fopen ("/etc/dhcp/dhcpd.conf", "w"));
      fclose (fopen ("/etc/dhcp/config_info.txt", "w"));

      exit (EXIT_FAILURE);
    }

  if (argc == 4 && !strcmp (argv[1], "network"))
    {
      ARGC_COUNT_ERROR (argc);

      snprintf (data->subnet, sizeof (argv[2])*MAX_LEN, "%s", argv[2]);
      snprintf (data->netmask, sizeof (argv[3])*MAX_LEN, "%s", argv[3]);
    }

  if (argc == 4 && !strcmp (argv[1], "range"))
    {
      ARGC_COUNT_ERROR (argc);

      snprintf (data->rangeUp, sizeof (argv[2])*MAX_LEN, "%s", argv[2]);
      snprintf (data->rangeDown, sizeof (argv[3])*MAX_LEN, "%s", argv[3]);
    }

  if (argc == 3  && !strcmp (argv[1], "default-router"))
    snprintf (data->gateway, sizeof (argv[2])*MAX_LEN, "%s", argv[2]);

  if (argc == 3  && !strcmp (argv[1], "dns-server"))
    snprintf (data->dns, sizeof (argv[2])*MAX_LEN, "%s", argv[2]);
}

void
initData (struct pool *data)
{
  char *val = MALLOC_AND_ERRCHECK (val, sizeof (char));
//TODO flag is the issue
  FILE *configInfo = fopen ("/etc/dhcp/config_info.txt", "w+");

  if (configInfo == NULL)
    exit (EXIT_FAILURE);

  fscanf (configInfo, "%s", val);
  snprintf (data->subnet, sizeof (val)*MAX_LEN, "%s", val);

  fscanf (configInfo,  "%s", val);
  snprintf (data->netmask, sizeof (val)*MAX_LEN, "%s", val);

  fscanf (configInfo,  "%s", val);
  snprintf (data->rangeUp, sizeof (val)*MAX_LEN, "%s", val);

  fscanf (configInfo,  "%s", val);
  snprintf (data->rangeDown, sizeof (val)*MAX_LEN, "%s", val);

  fscanf (configInfo,  "%s", val);
  snprintf (data->gateway,  sizeof (val)*MAX_LEN, "%s", val);

  fscanf (configInfo,  "%s", val);
  snprintf (data->dns, sizeof (val)*MAX_LEN, "%s", val);

  fclose (configInfo);

  free (val);
}

void
writeConfigFile (struct pool *data)
{
  char *tmp =  MALLOC_AND_ERRCHECK (tmp, sizeof (char));

  FILE *dhcpdconfig = fopen ("/etc/dhcp/dhcpd.conf", "w");

  if (dhcpdconfig == NULL)
    exit (EXIT_FAILURE);

  snprintf (tmp, MAX_LEN, "%s", "subnet ");
  strncat (tmp, data->subnet, sizeof (data->subnet)*MAX_LEN);

  strncat (tmp, " netmask ", MAX_LEN);
  strncat (tmp, data->netmask, sizeof (data->netmask)*MAX_LEN);
  strncat (tmp, " { \n", MAX_LEN);

  strncat (tmp, "range ", MAX_LEN);
  strncat (tmp, data->rangeUp, sizeof (data->rangeUp)*MAX_LEN);
  strncat (tmp, " ", MAX_LEN);

  strncat (tmp, data->rangeDown, sizeof (data->rangeDown)*MAX_LEN);
  strncat (tmp, "; \n", MAX_LEN);

  strncat (tmp, "option routers ", MAX_LEN);
  strncat (tmp, data->gateway, sizeof (data->gateway)*MAX_LEN);
  strncat (tmp, "; \n", MAX_LEN);

  strncat (tmp, "option domain-name-servers ", MAX_LEN);
  strncat (tmp, data->dns, sizeof (data->dns)*MAX_LEN);
  strncat (tmp, "; } \n", MAX_LEN);

  fputs (tmp, dhcpdconfig);

  fclose (dhcpdconfig);

  free (tmp);
}

void
writeBackUpFile (struct pool *data)
{
  char *tmp =  MALLOC_AND_ERRCHECK (tmp, sizeof (char));

  FILE *configInfo = fopen ("/etc/dhcp/config_info.txt", "w");

  if (configInfo == NULL)
    exit (EXIT_FAILURE);

  snprintf (tmp, sizeof (data->subnet)*MAX_LEN, "%s", data->subnet);
  strncat (tmp, "  \n", MAX_LEN);

  strncat (tmp, data->netmask, sizeof (data->netmask)*MAX_LEN);
  strncat (tmp, "  \n", MAX_LEN);

  strncat (tmp, data->rangeUp, sizeof (data->rangeUp)*MAX_LEN);
  strncat (tmp, "  \n", MAX_LEN);

  strncat (tmp, data->rangeDown, sizeof (data->rangeDown)*MAX_LEN);
  strncat (tmp, "  \n", MAX_LEN);

  strncat (tmp, data->gateway, sizeof (data->gateway)*MAX_LEN);
  strncat (tmp, " \n", MAX_LEN);

  strncat (tmp, data->dns, sizeof (data->dns)*MAX_LEN);
  strncat (tmp, " \n", MAX_LEN);

  fputs (tmp, configInfo);

  fclose (configInfo);

  free (tmp);
}

void
freeMem (struct  pool *data)
{
  free (data->subnet);
  free (data->netmask);
  free (data->rangeUp);
  free (data->rangeDown);
  free (data->gateway);
  free (data->dns);
}
