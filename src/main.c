/**
 * @file main.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief main file to config the dhcp server with user data.
 * @version 0.2.3
 * @date 23 Oct 2021
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
#include <string.h>

#include"dhcpd_conf.h"

int
main (int argc, char *argv)
{
  struct pool data;

  initMem (&data);
/*
 // while (1)
  {
    if (!strcmp (&argv[1], "exit"))
      break;
*/
   getData (argc, &argv, &data);
//}

  setData (&data);

 // pushData (&data);

  freeMem (&data);

  return 0;
}