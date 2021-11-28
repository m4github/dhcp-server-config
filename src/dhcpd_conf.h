/**
 * @file dhcpd_conf.h
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief  A library to config the dhcp server with user data.
 * @version 0.3.3
 * @date 23 Oct 2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#if !defined(_DHCPD_CONF_H)
#define _DHCPD_CONF_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/queue.h>

#define DHCP_BACKUP "/etc/dhcp/dhcp_backup.txt"
#define DHCP_CONFIG "/etc/dhcp/dhcpd.conf"
#define IP_LEN 15

struct pool
{
  char name[IP_LEN];
  char subnet[IP_LEN];
  char netmask[IP_LEN];
  char rangeUp[IP_LEN];
  char rangeDown[IP_LEN];
  char gateway[IP_LEN];
  char dns[IP_LEN];

  STAILQ_ENTRY (pool) next;
};

STAILQ_HEAD (stailqhead, pool);

int check_arg_count (int argc, int count);

void init_data (struct stailqhead *pool_head);
void get_data (int argc, char *argv[],
               struct stailqhead *pool_head);
void write_config_file (struct stailqhead *pool_head);
void write_backup_file (struct stailqhead *pool_head);

#endif