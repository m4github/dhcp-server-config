/**
 * @file main.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief main file to config the dhcp server with user data.
 * @version 0.2.0
 * @date 23 Oct 2021
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>

#include"dhcpd_conf.h"

int
main (int argc, char *argv)
{
  struct variable data;

  initMem (&data);

  initfile (&data);

  getNetwork (argc, &argv, &data);

  getRange (argc, &argv, &data);

  getGateway (argc, &argv, &data);

  getDNS (argc, &argv, &data);

  closeFile (&data);

  freeMem (&data);

  return 0;
}