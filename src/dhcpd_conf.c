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
init_data (struct pool *data, struct listhead head)
{
  FILE *configInfo = fopen ("/etc/dhcp/config_info.txt", "r");
  if (configInfo == NULL)
    {
      fprintf (stderr, "Failed to open config_info file. please try again.\n");
      if (fopen ("/etc/dhcp/config_info.txt", "w") == NULL)
        {
          fprintf (stderr, "Failed to open config_info file.\n");
          exit (EXIT_FAILURE);
        }
    }
  //TODO name nodes
  data = malloc (sizeof (struct pool));//TODO move it
  if (LIST_EMPTY (&head))
    {
      LIST_INIT (&head);
      LIST_INSERT_HEAD (&head, data, next);
      while (configInfo)
        {
          fscanf (configInfo, "%s", data->name);
          fscanf (configInfo, "%s", data->subnet);
          fscanf (configInfo, "%s", data->netmask);
          fscanf (configInfo, "%s", data->rangeUp);
          fscanf (configInfo, "%s", data->rangeDown);
          fscanf (configInfo, "%s", data->gateway);
          fscanf (configInfo, "%s", data->dns);

          struct pool *data = malloc (sizeof (struct pool));
          TAILQ_INSERT_TAIL (head, data, next); //struct tailhead 
        }
    }
  fclose (configInfo);
}

void
get_data (int argc, char *argv[], struct pool *data)
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

  else if (argc && !strcmp (argv[1], "ip dhcp pool"))
    {
      if (argument_counter (argc, 3))
        exit (EXIT_FAILURE);
      snprintf (data->name, strlen (argv[2]), "%s", argv[2]);
    }

  else if (argc  && !strcmp (argv[1], "network"))
    {
      if (argument_counter (argc, 4))
        exit (EXIT_FAILURE);

      snprintf (data->subnet, strlen (argv[2]) + 1, "%s", argv[2]);
      snprintf (data->netmask, strlen (argv[3]) + 1, "%s", argv[3]);
    }

  else if (argc && !strcmp (argv[1], "range"))
    {
      if (argument_counter (argc, 4))
        exit (EXIT_FAILURE);

      snprintf (data->rangeUp, strlen (argv[2]) + 1, "%s", argv[2]);
      snprintf (data->rangeDown, strlen (argv[3]) + 1, "%s", argv[3]);
    }

  else if (argc && !strcmp (argv[1], "default-router"))
    {
      if (argument_counter (argc, 3))
        exit (EXIT_FAILURE);

      snprintf (data->gateway, strlen (argv[2]) + 1, "%s", argv[2]);
    }

  else if (argc && !strcmp (argv[1], "dns-server"))
    {
      if (argument_counter (argc, 3))
        exit (EXIT_FAILURE);

      snprintf (data->dns, strlen (argv[2]) + 1, "%s", argv[2]);
    }

  else
    {
      fprintf (stderr, "Argument is not defined.\n");
      exit (EXIT_FAILURE);
    }
  return;
}

void
write_config_file (struct pool *data)
{
  char *buffer = (char *)malloc (sizeof (char) * 256);
  if (buffer == NULL)
    {
      fprintf (stderr, "couldnt allocate memory.");
      exit (EXIT_FAILURE);
    }

  FILE *dhcpdconfig = fopen ("/etc/dhcp/dhcpd.conf", "w");
  if (dhcpdconfig == NULL)
    exit (EXIT_FAILURE);

  snprintf (buffer, 8, "%s", "subnet ");
  strncat (buffer, data->subnet, strlen (data->subnet));

  strncat (buffer, " netmask ", 10);
  strncat (buffer, data->netmask, strlen (data->netmask));
  strncat (buffer, "{\n", MAX_LEN);

  strncat (buffer, "range ", 7);
  strncat (buffer, data->rangeUp, strlen (data->rangeUp));
  strncat (buffer, " ", MAX_LEN);

  strncat (buffer, data->rangeDown, strlen (data->rangeDown));
  strncat (buffer, ";\n", MAX_LEN);

  strncat (buffer, "option routers ", 16);
  strncat (buffer, data->gateway, strlen (data->gateway));
  strncat (buffer, ";\n", MAX_LEN);

  strncat (buffer, "option domain-name-servers ", 28);
  strncat (buffer, data->dns, strlen (data->dns));
  strncat (buffer, ";}", MAX_LEN);

  fputs (buffer, dhcpdconfig);

  fclose (dhcpdconfig);

  free (buffer);
}

void
write_backup_file (struct pool *data)
{
  char *buffer = (char *)malloc (sizeof (char) * 128);
  if (buffer == NULL)
    {
      fprintf (stderr, "couldnt allocate memory.");
      exit (EXIT_FAILURE);
    }

  FILE *configInfo = fopen ("/etc/dhcp/config_info.txt", "w");
  if (configInfo == NULL)
    exit (EXIT_FAILURE);

  snprintf (buffer, strlen (data->subnet), "%s", data->subnet);
  strncat (buffer, "\n", MAX_LEN);

  strncat (buffer, data->netmask, strlen (data->netmask));
  strncat (buffer, "\n", MAX_LEN);

  strncat (buffer, data->rangeUp, strlen (data->rangeUp));
  strncat (buffer, "\n", MAX_LEN);

  strncat (buffer, data->rangeDown, strlen (data->rangeDown));
  strncat (buffer, "\n", MAX_LEN);

  strncat (buffer, data->gateway, strlen (data->gateway));
  strncat (buffer, "\n", MAX_LEN);

  strncat (buffer, data->dns, strlen (data->dns));
  strncat (buffer, "\n", MAX_LEN);

  fputs (buffer, configInfo);

  fclose (configInfo);

  free (buffer);
}

