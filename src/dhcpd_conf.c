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
init_data (struct pool *data, struct tailhead head)
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
    }

  data = malloc (sizeof (struct pool));
  TAILQ_INSERT_HEAD (&head, data, next);

  while (!feof (configInfo))
    {
      fscanf (configInfo, "%s", data->name);
      fscanf (configInfo, "%s", data->subnet);
      fscanf (configInfo, "%s", data->netmask);
      fscanf (configInfo, "%s", data->rangeUp);
      fscanf (configInfo, "%s", data->rangeDown);
      fscanf (configInfo, "%s", data->gateway);
      fscanf (configInfo, "%s", data->dns);

      struct pool *data = malloc (sizeof (struct pool));
      TAILQ_INSERT_TAIL (&head, data, next);
    }
  fclose (configInfo);
}

void
get_data (int argc, char *argv[], struct pool *data, struct tailhead head)
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

      data = malloc (sizeof (struct pool));
      TAILQ_INSERT_TAIL (&head, data, next);
      snprintf (data->name, strlen (argv[2]), "%s", argv[2]);
    }

  else if (argc  && !strcmp (argv[2], "network"))
    {
      if (argument_counter (argc, 5))
        exit (EXIT_FAILURE);

      TAILQ_FOREACH (data, &head, next)
      {
        if (!strcmp (data->name, argv[1]))
          {
            snprintf (data->subnet, strlen (argv[2]) + 1, "%s", argv[2]);
            snprintf (data->netmask, strlen (argv[3]) + 1, "%s", argv[3]);
          }
      }
      //TODO print err -> no *name* pool /add it for all options
    }

  else if (argc && !strcmp (argv[2], "range"))
    {
      if (argument_counter (argc, 5))
        exit (EXIT_FAILURE);

      TAILQ_FOREACH (data, &head, next)
      {
        if (!strcmp (data->name, argv[1]))
          {
            snprintf (data->rangeUp, strlen (argv[2]) + 1, "%s", argv[2]);
            snprintf (data->rangeDown, strlen (argv[3]) + 1, "%s", argv[3]);
          }
      }
    }

  else if (argc && !strcmp (argv[2], "default-router"))
    {
      if (argument_counter (argc, 4))
        exit (EXIT_FAILURE);

      TAILQ_FOREACH (data, &head, next)
      {
        if (!strcmp (data->name, argv[1]))
          snprintf (data->gateway, strlen (argv[2]) + 1, "%s", argv[2]);
      }
    }

  else if (argc && !strcmp (argv[2], "dns-server"))
    {
      if (argument_counter (argc, 4))
        exit (EXIT_FAILURE);

      TAILQ_FOREACH (data, &head, next)
      {
        if (!strcmp (data->name, argv[1]))
          snprintf (data->dns, strlen (argv[2]) + 1, "%s", argv[2]);
      }
    }

  else
    {
      fprintf (stderr, "Argument is not defined.\n");
      exit (EXIT_FAILURE);
    }
  return;
}

void
write_config_file (struct pool *data, struct tailhead head)
{
  char *buffer = (char *)malloc (sizeof (struct pool) * 256);
  if (buffer == NULL)
    {
      fprintf (stderr, "couldnt allocate memory.");
      exit (EXIT_FAILURE);
    }

  FILE *dhcpdconfig = fopen ("/etc/dhcp/dhcpd.conf", "w");
  if (dhcpdconfig == NULL)
    exit (EXIT_FAILURE);

  TAILQ_FOREACH (data, &head, next)
  {
    strcat (buffer, "#poll ");
    strcat (buffer, data->name);
    strcat (buffer, "\n");

    strcat (buffer, "subnet ");
    strcat (buffer, data->subnet);

    strcat (buffer, " netmask ");
    strcat (buffer, data->netmask);
    strcat (buffer, "{\n");

    strcat (buffer, "range ");
    strcat (buffer, data->rangeUp);
    strcat (buffer, " ");

    strcat (buffer, data->rangeDown);
    strcat (buffer, ";\n");

    strcat (buffer, "option routers ");
    strcat (buffer, data->gateway);
    strcat (buffer, ";\n");

    strcat (buffer, "option domain-name-servers ");
    strcat (buffer, data->dns);
    strcat (buffer, ";}");
  }
  fputs (buffer, dhcpdconfig);

  fclose (dhcpdconfig);
  free (buffer);
}

void
write_backup_file (struct pool *data, struct tailhead head)
{
  char *buffer = (char *)malloc (sizeof (struct pool) * 254);
  if (buffer == NULL)
    {
      fprintf (stderr, "couldnt allocate memory.");
      exit (EXIT_FAILURE);
    }

  FILE *configInfo = fopen ("/etc/dhcp/config_info.txt", "w");
  if (configInfo == NULL)
    exit (EXIT_FAILURE);

  TAILQ_FOREACH (data, &head, next)
  {
    strcat (buffer, data->name);
    strcat (buffer, "\n");

    strcat (buffer, data->subnet);
    strcat (buffer, "\n");

    strcat (buffer, data->netmask);
    strcat (buffer, "\n");

    strcat (buffer, data->rangeUp);
    strcat (buffer, "\n");

    strcat (buffer, data->rangeDown);
    strcat (buffer, "\n");

    strcat (buffer, data->gateway);
    strcat (buffer, "\n");

    strcat (buffer, data->dns);
    strcat (buffer, "\n");
  }
  fputs (buffer, configInfo);

  fclose (configInfo);
  free (buffer);
}

