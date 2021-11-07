/**
 * @file main.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief main file to config the dhcp server with user data.
 * @version 0.3.5
 * @date 23 Oct 2021
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "dhcpd_conf.h"

int
main (int argc, char *argv[])
{
  struct pool data;

  char *args[] = {"service isc-dhcp-server restart", NULL};

  if (!argv[1])
    {
      fprintf (stderr, "Add any arguments.\n");
      exit (EXIT_FAILURE);
    }

  init_data (&data);

  get_data (argc, argv, &data);

  write_config_file (&data);
  write_backup_file (&data);

  if (execvp (args[0], args) == -1)
    {
      fprintf (stderr, "\e[31m[Failed to restart server.]\n");
      exit (EXIT_FAILURE);
    }

  return 0;
}
