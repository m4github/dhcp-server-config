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
check_arg_count (int argc, int count)
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
init_data (struct stailqhead *pool_head)
{
  struct pool *data;
  FILE *backup_fp = fopen (DHCP_BACKUP, "r");
  if (backup_fp == NULL)
    {
      backup_fp = fopen (DHCP_BACKUP, "w");
      if (backup_fp == NULL)
        {
          fprintf (stderr, "Failed to open config_info file.\n");
          exit (EXIT_FAILURE);
        }
    }

  fseek (backup_fp, 0, SEEK_END);
  long size = ftell (backup_fp);
  fseek (backup_fp, 0, SEEK_SET);

  while (ftell (backup_fp) < size - 2)
    {
      data = malloc (sizeof (struct pool));

      fscanf (backup_fp, "%s", data->name);
      fscanf (backup_fp, "%s", data->subnet);
      fscanf (backup_fp, "%s", data->netmask);
      fscanf (backup_fp, "%s", data->rangeUp);
      fscanf (backup_fp, "%s", data->rangeDown);
      fscanf (backup_fp, "%s", data->gateway);
      fscanf (backup_fp, "%s", data->dns);

      STAILQ_INSERT_TAIL (pool_head, data, next);
    }
  fclose (backup_fp);
}

void
get_data (const int argc, char *argv[], struct stailqhead *pool_head)
{
  struct pool *data;
  if (argc && !strcmp (argv[1], "-reset"))
    {
      FILE *pointer1 = fopen (DHCP_CONFIG, "w");
      FILE *pointer2 = fopen (DHCP_BACKUP, "w");

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

  else if (argc > 0 && !strcmp (argv[1], "ip-dhcp-pool"))
    {
      if (check_arg_count (argc, 3))
        exit (EXIT_FAILURE);

      STAILQ_FOREACH (data, pool_head, next)
      {
        if (!strcmp (argv[2], data->name))
          {
            fprintf (stderr, "pool name already exist.\n");
            exit (EXIT_FAILURE);
          }
      }
      data = malloc (sizeof (struct pool));
      STAILQ_INSERT_TAIL (pool_head, data, next);
      snprintf (data->name, strlen (argv[2]) + 1, "%s", argv[2]);
      sprintf (data->subnet, "%s", "-");
      sprintf (data->netmask, "%s", "-");
      sprintf (data->rangeUp, "%s", "-");
      sprintf (data->rangeDown, "%s", "-");
      sprintf (data->gateway, "%s", "-");
      sprintf (data->dns, "%s", "-");
      return;
    }

  else if (argc > 0  && !strcmp (argv[2], "network"))
    {
      if (check_arg_count (argc, 5))
        exit (EXIT_FAILURE);

      STAILQ_FOREACH (data, pool_head, next)
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

  else if (argc > 0 && !strcmp (argv[2], "range"))
    {
      if (check_arg_count (argc, 5))
        exit (EXIT_FAILURE);

      STAILQ_FOREACH (data, pool_head, next)
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

  else if (argc > 0 && !strcmp (argv[2], "default-router"))
    {
      if (check_arg_count (argc, 4))
        exit (EXIT_FAILURE);

      STAILQ_FOREACH (data, pool_head, next)
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

  else if (argc > 0 && !strcmp (argv[2], "dns-server"))
    {
      if (check_arg_count (argc, 4))
        exit (EXIT_FAILURE);

      STAILQ_FOREACH (data, pool_head, next)
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
write_config_file (struct stailqhead *pool_head)
{
  struct pool *data;
  FILE *dhcpdconfig = fopen (DHCP_CONFIG, "w");
  if (dhcpdconfig == NULL)
    {
      fprintf (stderr, "Failed to open file.");
      exit (EXIT_FAILURE);
    }

  STAILQ_FOREACH (data, pool_head, next)
  {
    fprintf (dhcpdconfig, "%s", "#pool ");
    fprintf (dhcpdconfig, "%s", data->name);
    fprintf (dhcpdconfig, "%s", "\n");

    fprintf (dhcpdconfig, "%s", "subnet ");
    fprintf (dhcpdconfig, "%s", data->subnet);

    fprintf (dhcpdconfig, "%s", " netmask ");
    fprintf (dhcpdconfig, "%s", data->netmask);
    fprintf (dhcpdconfig, "%s", "{\n");

    fprintf (dhcpdconfig, "%s", "range ");
    fprintf (dhcpdconfig, "%s", data->rangeUp);
    fprintf (dhcpdconfig, "%s", " ");

    fprintf (dhcpdconfig, "%s", data->rangeDown);
    fprintf (dhcpdconfig, "%s", ";\n");

    fprintf (dhcpdconfig, "%s", "option routers ");
    fprintf (dhcpdconfig, "%s", data->gateway);
    fprintf (dhcpdconfig, "%s", ";\n");

    fprintf (dhcpdconfig, "%s", "option domain-name-servers ");
    fprintf (dhcpdconfig, "%s", data->dns);
    fprintf (dhcpdconfig, "%s", ";}\n");
  }
  fclose (dhcpdconfig);
}

void
write_backup_file (struct stailqhead *pool_head)
{
  struct pool *data;
  FILE *backup_fp = fopen (DHCP_BACKUP, "w");
  if (backup_fp == NULL)
    {
      fprintf (stderr, "Failed to open file.");
      exit (EXIT_FAILURE);
    }
  STAILQ_FOREACH (data, pool_head, next)
  {
    fprintf (backup_fp, "%s", data->name);
    fprintf (backup_fp, "%s", "\n");

    fprintf (backup_fp, "%s", data->subnet);
    fprintf (backup_fp, "%s", "\n");

    fprintf (backup_fp, "%s", data->netmask);
    fprintf (backup_fp, "%s", "\n");

    fprintf (backup_fp, "%s", data->rangeUp);
    fprintf (backup_fp, "%s", "\n");

    fprintf (backup_fp, "%s", data->rangeDown);
    fprintf (backup_fp, "%s", "\n");

    fprintf (backup_fp, "%s", data->gateway);
    fprintf (backup_fp, "%s", "\n");

    fprintf (backup_fp, "%s", data->dns);
    fprintf (backup_fp, "%s", "\n");
  }
  fclose (backup_fp);
}