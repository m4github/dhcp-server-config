/**
 * @file dhcpd_conf.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief config the dhcp server with user data.
 * @version 0.6.8
 * @date 23 Oct 2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "dhcpd_conf.h"

int
argument_counter (int argc, int count)
{
  if (argc < count)
    {
      fprintf (stderr, "Add more arguments\n");
      return 1;
    }
  else
    return 0;
}

void
init_data (struct pool *data, struct stailqhead *head)
{
  FILE *configInfo = fopen ("/etc/dhcp/config_info.txt", "r");
  if (configInfo == NULL)
    {
      configInfo = fopen ("/etc/dhcp/config_info.txt", "w");
      fprintf (stderr, "Failed to open config_info file. please try again.\n");
      if (configInfo == NULL)
        {
          fprintf (stderr, "Failed to open config_info file.\n");
          exit (EXIT_FAILURE);
        }
      exit (EXIT_FAILURE);
    }

  fseek (configInfo, 0, SEEK_END);
  long size = ftell (configInfo);
  fseek (configInfo, 0, SEEK_SET);

  while (ftell (configInfo) < size - 2)
    {
      data = malloc (sizeof (struct pool));

      fscanf (configInfo, "%s", data->name);
      fscanf (configInfo, "%s", data->subnet);
      fscanf (configInfo, "%s", data->netmask);
      fscanf (configInfo, "%s", data->rangeUp);
      fscanf (configInfo, "%s", data->rangeDown);
      fscanf (configInfo, "%s", data->gateway);
      fscanf (configInfo, "%s", data->dns);

      STAILQ_INSERT_TAIL (head, data, next);
    }
  fclose (configInfo);
}

void
get_data (int argc, char *argv[], struct pool *data, struct stailqhead *head)
{
  if (argc && !strcmp (argv[1], "-reset"))
    {
      FILE *pointer1 = fopen ("/etc/dhcp/dhcpd.conf", "w");
      FILE *pointer2 = fopen ("/etc/dhcp/config_info.txt", "w");

      if (pointer1)
        {
          fclose (pointer1);

          if (pointer2)
            fclose (pointer2);
          else
            exit (EXIT_FAILURE);

          exit (EXIT_SUCCESS);
        }
      else
        fclose (pointer2);
      exit (EXIT_FAILURE);
    }

  else if (argc && !strcmp (argv[1], "exit"))
    exit (EXIT_SUCCESS);

  else if (argc && !strcmp (argv[1], "ip-dhcp-pool"))
    {
      if (argument_counter (argc, 3))
        exit (EXIT_FAILURE);

      STAILQ_FOREACH (data, head, next)
      {
        if (!strcmp (argv[2], data->name))
          {
            fprintf (stderr, "pool name already exist.\n");
            exit (EXIT_FAILURE);
          }
      }
      data = malloc (sizeof (struct pool));
      STAILQ_INSERT_TAIL (head, data, next);
      snprintf (data->name, strlen (argv[2]) + 1, "%s", argv[2]);
      sprintf (data->subnet, "%s", "-");
      sprintf (data->netmask, "%s", "-");
      sprintf (data->rangeUp, "%s", "-");
      sprintf (data->rangeDown, "%s", "-");
      sprintf (data->gateway, "%s", "-");
      return;
    }

  else if (argc  && !strcmp (argv[2], "network"))
    {
      if (argument_counter (argc, 5))
        exit (EXIT_FAILURE);

      STAILQ_FOREACH (data, head, next)
      {
        if (!strcmp (data->name, argv[1]))
          {
            snprintf (data->subnet, strlen (argv[3]) + 1, "%s", argv[3]);
            snprintf (data->netmask, strlen (argv[4]) + 1, "%s", argv[4]);
            return;
          }
      }
      fprintf (stderr, "pool name not found.\n");
      exit (EXIT_FAILURE);
    }

  else if (argc && !strcmp (argv[2], "range"))
    {
      if (argument_counter (argc, 5))
        exit (EXIT_FAILURE);

      STAILQ_FOREACH (data, head, next)
      {
        if (!strcmp (data->name, argv[1]))
          {
            snprintf (data->rangeUp, strlen (argv[3]) + 1, "%s", argv[3]);
            snprintf (data->rangeDown, strlen (argv[4]) + 1, "%s", argv[4]);
            return;
          }
      }
      fprintf (stderr, "pool name not found.\n");
      exit (EXIT_FAILURE);
    }

  else if (argc && !strcmp (argv[2], "default-router"))
    {
      if (argument_counter (argc, 4))
        exit (EXIT_FAILURE);

      STAILQ_FOREACH (data, head, next)
      {
        if (!strcmp (data->name, argv[1]))
          {
            snprintf (data->gateway, strlen (argv[3]) + 1, "%s", argv[3]);
            return;
          }
      }
      fprintf (stderr, "pool name not found.\n");
      exit (EXIT_FAILURE);
    }

  else if (argc && !strcmp (argv[2], "dns-server"))
    {
      if (argument_counter (argc, 4))
        exit (EXIT_FAILURE);

      STAILQ_FOREACH (data, head, next)
      {
        if (!strcmp (data->name, argv[1]))
          {
            snprintf (data->dns, strlen (argv[3]) + 1, "%s", argv[3]);
            return;
          }
      }
      fprintf (stderr, "pool name not found.\n");
      exit (EXIT_FAILURE);
    }

  else
    {
      fprintf (stderr, "Argument is not defined.\n");
      exit (EXIT_FAILURE);
    }
}

void
write_config_file (struct pool *data, struct stailqhead *head)
{
  FILE *dhcpdconfig = fopen ("/etc/dhcp/dhcpd.conf", "w");
  if (dhcpdconfig == NULL)
    {
      fprintf (stderr, "Failed to open file.");
      exit (EXIT_FAILURE);
    }

  STAILQ_FOREACH (data, head, next)
  {
    FIELD_TMPLATE (data->name);
    fprintf (dhcpdconfig, "%s", "#pool ");
    fprintf (dhcpdconfig, "%s", data->name);
    fprintf (dhcpdconfig, "%s", "\n");

    FIELD_TMPLATE (data->subnet);
    fprintf (dhcpdconfig, "%s", "subnet ");
    fprintf (dhcpdconfig, "%s", data->subnet);

    FIELD_TMPLATE (data->netmask);
    fprintf (dhcpdconfig, "%s", " netmask ");
    fprintf (dhcpdconfig, "%s", data->netmask);
    fprintf (dhcpdconfig, "%s", "{\n");

    FIELD_TMPLATE (data->rangeUp);
    fprintf (dhcpdconfig, "%s", "range ");
    fprintf (dhcpdconfig, "%s", data->rangeUp);
    fprintf (dhcpdconfig, "%s", " ");

    FIELD_TMPLATE (data->rangeDown);
    fprintf (dhcpdconfig, "%s", data->rangeDown);
    fprintf (dhcpdconfig, "%s", ";\n");

    FIELD_TMPLATE (data->gateway);
    fprintf (dhcpdconfig, "%s", "option routers ");
    fprintf (dhcpdconfig, "%s", data->gateway);
    fprintf (dhcpdconfig, "%s", ";\n");

    FIELD_TMPLATE (data->dns);
    fprintf (dhcpdconfig, "%s", "option domain-name-servers ");
    fprintf (dhcpdconfig, "%s", data->dns);
    fprintf (dhcpdconfig, "%s", ";}\n");
  }
  fclose (dhcpdconfig);
}

void
write_backup_file (struct pool *data, struct stailqhead *head)
{
  FILE *configInfo = fopen ("/etc/dhcp/config_info.txt", "w");
  if (configInfo == NULL)
    {
      fprintf (stderr, "Failed to open file.");
      exit (EXIT_FAILURE);
    }
  STAILQ_FOREACH (data, head, next)
  {
    fprintf (configInfo, "%s", data->name);
    fprintf (configInfo, "%s", "\n");

    fprintf (configInfo, "%s", data->subnet);
    fprintf (configInfo, "%s", "\n");

    fprintf (configInfo, "%s", data->netmask);
    fprintf (configInfo, "%s", "\n");

    fprintf (configInfo, "%s", data->rangeUp);
    fprintf (configInfo, "%s", "\n");

    fprintf (configInfo, "%s", data->rangeDown);
    fprintf (configInfo, "%s", "\n");

    fprintf (configInfo, "%s", data->gateway);
    fprintf (configInfo, "%s", "\n");

    fprintf (configInfo, "%s", data->dns);
    fprintf (configInfo, "%s", "\n");
  }
  fclose (configInfo);
}