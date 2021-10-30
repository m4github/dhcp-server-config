/**
 * @file main.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief main file to config the dhcp server with user data.
 * @version 0.2.4
 * @date 23 Oct 2021
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"dhcpd_conf.h"

int
main (int argc, char *argv[])
{
  struct pool data;

  initMem (&data);

  initData (&data);

  if (argc && !strcmp (argv[1], "exit"))
    return 0;

  getData (argc, argv, &data);

  writeConfigFile (&data);

  writeBackUpFile (&data);

  if (system ("sudo service isc-dhcp-server restart") != 0)
    {
      fprintf (stderr, "complete the config file.\n");
      exit (EXIT_FAILURE);
    }

  freeMem (&data);

  return 0;
}
