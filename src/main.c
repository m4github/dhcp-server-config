/**
 * @file main.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief main file to config the dhcp server with user data.
 * @version 0.1.0
 * @date 23 Oct 2021
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>

#include"dhcpd_conf.h"

int
main()
{
  struct variable data;

  initMem (&data);

  setLoc (&data);

  getSubnet (&data);

  getnetMask (&data);

  getRange (&data);

  getGateway (&data);

  getDNS (&data);

  closeFile (&data);

  freeMem (&data);

}
