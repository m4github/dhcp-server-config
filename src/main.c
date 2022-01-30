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

#include "dhcpd_conf.h"

int
main (const int argc, char *argv[])
{
  struct pool *dhcp_pool;
 refactore
  struct stailqhead pool_head;
  STAILQ_INIT (&pool_head);


  struct listhead head;
  
 main
  char *args[] = {"service isc-dhcp-server restart", NULL};

  if (argc == 0)
    {
      fprintf (stderr, "Add any arguments.\n");
      exit (EXIT_FAILURE);
    }

 refactore
  init_data (&pool_head);

  get_data (argc, argv, &pool_head);

  write_config_file (&pool_head);
  write_backup_file (&pool_head);

  init_data (dhcp_pool, head);

  get_data (argc, argv, dhcp_pool);
  LIST_INSERT_AFTER (dhcp_pool, dhcp_pool, next);

  write_config_file (dhcp_pool);
  write_backup_file (dhcp_pool);
 main

  if (execvp (args[0], args) == -1)
    {
      fprintf (stderr, "\e[31m[Failed to restart server.]\n");
      exit (EXIT_FAILURE);
    }

  return 0;
}
