/**
 * @file dhcpd_conf.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief config the dhcp server with user data.
 * @version 0.6.7
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

  if (argc  && !strcmp (argv[1], "network"))
    {
      ARGC_4COUNT_ERROR (argc);

      snprintf (data->subnet, strlen (argv[2]), "%s", argv[2]);
      snprintf (data->netmask, strlen (argv[3]), "%s", argv[3]);
    }

  if (argc && !strcmp (argv[1], "range"))
    {
      ARGC_4COUNT_ERROR (argc);

      snprintf (data->rangeUp, strlen (argv[2]), "%s", argv[2]);
      snprintf (data->rangeDown, strlen (argv[3]), "%s", argv[3]);
    }

  if (argc && !strcmp (argv[1], "default-router"))
    {
      ARGC_3COUNT_ERROR (argc);

      snprintf (data->gateway, strlen (argv[2]), "%s", argv[2]);
    }

  if (argc && !strcmp (argv[1], "dns-server"))
    {
      ARGC_3COUNT_ERROR (argc);

      snprintf (data->dns, strlen (argv[2]), "%s", argv[2]);
    }
}

void
initData (struct pool *data)
{
  char *val = MALLOC_AND_ERRCHECK (val, sizeof (char));

  FILE *configInfo = fopen ("/etc/dhcp/config_info.txt", "r");
  if (configInfo == NULL)
    return;

  fscanf (configInfo, "%s", val);
  snprintf (data->subnet, strlen (val), "%s", val);

  fscanf (configInfo, "%s", val);
  snprintf (data->netmask, strlen (val), "%s", val);

  fscanf (configInfo, "%s", val);
  snprintf (data->rangeUp, strlen (val), "%s", val);

  fscanf (configInfo, "%s", val);
  snprintf (data->rangeDown, strlen (val), "%s", val);

  fscanf (configInfo, "%s", val);
  snprintf (data->gateway,  strlen (val), "%s", val);

  fscanf (configInfo, "%s", val);
  snprintf (data->dns, strlen (val), "%s", val);

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
  strncat (tmp, data->subnet, strlen (data->subnet));

  strncat (tmp, " netmask ", MAX_LEN);
  strncat (tmp, data->netmask, strlen (data->netmask));
  strncat (tmp, " { \n", MAX_LEN);

  strncat (tmp, "range ", MAX_LEN);
  strncat (tmp, data->rangeUp, strlen (data->rangeUp));
  strncat (tmp, " ", MAX_LEN);

  strncat (tmp, data->rangeDown, strlen (data->rangeDown));
  strncat (tmp, "; \n", MAX_LEN);

  strncat (tmp, "option routers ", MAX_LEN);
  strncat (tmp, data->gateway, strlen (data->gateway));
  strncat (tmp, "; \n", MAX_LEN);

  strncat (tmp, "option domain-name-servers ", MAX_LEN);
  strncat (tmp, data->dns, strlen (data->dns));
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

  snprintf (tmp, strlen (data->subnet), "%s", data->subnet);
  strncat (tmp, "  \n", MAX_LEN);

  strncat (tmp, data->netmask, strlen (data->netmask));
  strncat (tmp, "  \n", MAX_LEN);

  strncat (tmp, data->rangeUp, strlen (data->rangeUp));
  strncat (tmp, "  \n", MAX_LEN);

  strncat (tmp, data->rangeDown, strlen (data->rangeDown));
  strncat (tmp, "  \n", MAX_LEN);

  strncat (tmp, data->gateway, strlen (data->gateway));
  strncat (tmp, " \n", MAX_LEN);

  strncat (tmp, data->dns, strlen (data->dns));
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
