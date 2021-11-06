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
get_data (int argc, char *argv[], struct pool *data)
{
  if (argc && !strcmp (argv[1], "-reset"))
    {
      FILE *tmp1 = fopen ("/etc/dhcp/dhcpd.conf", "w");
      FILE *tmp2 = fopen ("/etc/dhcp/config_info.txt", "w");

      if (tmp1 && tmp2)
        {
          fclose (tmp1);
          fclose (tmp2);
          exit (EXIT_SUCCESS);
        }
      else
        exit (EXIT_FAILURE);
    }

  else if (argc  && !strcmp (argv[1], "network"))
    {
      ARGC_4COUNT_ERROR (argc);

      snprintf (data->subnet, strlen (argv[2]), "%s", argv[2]);
      snprintf (data->netmask, strlen (argv[3]), "%s", argv[3]);
    }

  else if (argc && !strcmp (argv[1], "range"))
    {
      ARGC_4COUNT_ERROR (argc);

      snprintf (data->rangeUp, strlen (argv[2]), "%s", argv[2]);
      snprintf (data->rangeDown, strlen (argv[3]), "%s", argv[3]);
    }

  else if (argc && !strcmp (argv[1], "default-router"))
    {
      ARGC_3COUNT_ERROR (argc);

      snprintf (data->gateway, strlen (argv[2]), "%s", argv[2]);
    }

  else if (argc && !strcmp (argv[1], "dns-server"))
    {
      ARGC_3COUNT_ERROR (argc);

      snprintf (data->dns, strlen (argv[2]), "%s", argv[2]);
    }
}

void
init_data (struct pool *data)
{
  char *val = (char *)malloc (sizeof (char) * 1024);

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
  snprintf (data->gateway, strlen (val), "%s", val);

  fscanf (configInfo, "%s", val);
  snprintf (data->dns, strlen (val), "%s", val);

  fclose (configInfo);

  free (val);
}

void
write_config_file (struct pool *data)
{
  char *buffer = (char *)malloc (sizeof (char) * 1024);

  FILE *dhcpdconfig = fopen ("/etc/dhcp/dhcpd.conf", "w");
  if (dhcpdconfig == NULL)
    exit (EXIT_FAILURE);

  snprintf (buffer, MAX_LEN, "%s", "subnet ");
  strncat (buffer, data->subnet, strlen (data->subnet));

  strncat (buffer, " netmask ", MAX_LEN);
  strncat (buffer, data->netmask, strlen (data->netmask));
  strncat (buffer, " { \n", MAX_LEN);

  strncat (buffer, "range ", MAX_LEN);
  strncat (buffer, data->rangeUp, strlen (data->rangeUp));
  strncat (buffer, " ", MAX_LEN);

  strncat (buffer, data->rangeDown, strlen (data->rangeDown));
  strncat (buffer, "; \n", MAX_LEN);

  strncat (buffer, "option routers ", MAX_LEN);
  strncat (buffer, data->gateway, strlen (data->gateway));
  strncat (buffer, "; \n", MAX_LEN);

  strncat (buffer, "option domain-name-servers ", MAX_LEN);
  strncat (buffer, data->dns, strlen (data->dns));
  strncat (buffer, "; }\n", MAX_LEN);

  fputs (buffer, dhcpdconfig);

  fclose (dhcpdconfig);

  free (buffer);
}

void
write_backup_file (struct pool *data)
{
  char *buffer = (char *)malloc (sizeof (char) * 1024);

  FILE *configInfo = fopen ("/etc/dhcp/config_info.txt", "w");
  if (configInfo == NULL)
    exit (EXIT_FAILURE);

  snprintf (buffer, strlen (data->subnet), "%s", data->subnet);
  strncat (buffer, "  \n", MAX_LEN);

  strncat (buffer, data->netmask, strlen (data->netmask));
  strncat (buffer, "  \n", MAX_LEN);

  strncat (buffer, data->rangeUp, strlen (data->rangeUp));
  strncat (buffer, "  \n", MAX_LEN);

  strncat (buffer, data->rangeDown, strlen (data->rangeDown));
  strncat (buffer, "  \n", MAX_LEN);

  strncat (buffer, data->gateway, strlen (data->gateway));
  strncat (buffer, " \n", MAX_LEN);

  strncat (buffer, data->dns, strlen (data->dns));
  strncat (buffer, " \n", MAX_LEN);

  fputs (buffer, configInfo);

  fclose (configInfo);

  free (buffer);
}

