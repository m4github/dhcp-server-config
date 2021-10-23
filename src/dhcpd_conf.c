/**
 * @file dhcpd_conf.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief config the dhcp server with user data.
 * @version 0.2.1
 * @date 21 Oct 2021
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dhcpd_conf.h"

#define MAX_LEN 1024

void
initMem (struct  variable *data)
{

  MALLOC_AND_ERRCHECK (data->subnet, sizeof (char));

  MALLOC_AND_ERRCHECK (data->netmask, sizeof (char));

  MALLOC_AND_ERRCHECK (data->rangeUp, sizeof (char));

  MALLOC_AND_ERRCHECK (data->rangeDown, sizeof (char));

  MALLOC_AND_ERRCHECK (data->gateway, sizeof (char));

  MALLOC_AND_ERRCHECK (data->dns, sizeof (char));

  MALLOC_AND_ERRCHECK (data->configLoc, sizeof (char));

}
char
getInput()
{
  char *input = (char *)malloc (sizeof (char) * MAX_LEN);

  MALLOC_AND_ERRCHECK (input, MAX_LEN);

  size_t size = sizeof (input);

  getline (&input, &size, stdin);

  input[strlen (input) - 1] = '\0';

  input = strtok (input, " ");

  if (!input)

    input = (char *)malloc (sizeof (char) * MAX_LEN);

  MALLOC_AND_ERRCHECK (input, MAX_LEN);

  return input;

// free (input);
}

void
getSubnet (struct variable *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);

  strncpy (data->subnet, getInput(), (size_t)MAX_LEN);

  sprintf (tmp, "subnet ");
  sprintf (tmp, data->subnet);

  data->dhcpdconfig = fopen (data->configLoc, "w");

  if (data->dhcpdconfig == NULL)
  {
    errno = ENOENT;
    exit (errno);
  }

  fputs (tmp, data->dhcpdconfig);

  free (tmp);
}

void
getnetMask (struct variable *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);

  strncpy (data->netmask, getInput(), (size_t)MAX_LEN);

  sprintf (tmp, " netmask ");
  sprintf (tmp, data->netmask);
  sprintf (tmp, " { ");

  data->dhcpdconfig = fopen (data->configLoc, "w");

  if (data->dhcpdconfig == NULL)
  {
    errno = ENOENT;
    exit (errno);
  }

  fputs (tmp, data->dhcpdconfig);

  free (tmp);
}

void
getRange (struct variable *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);

  strncpy (data->rangeUp, getInput(), (size_t)MAX_LEN);
  strncpy (data->rangeDown, getInput(), (size_t)MAX_LEN);

  sprintf (tmp, "range ");
  sprintf (tmp, data->rangeUp);
  sprintf (tmp, " ");
  sprintf (tmp, data->rangeDown);
  sprintf (tmp, ";");

  data->dhcpdconfig = fopen (data->configLoc, "w");

  if (data->dhcpdconfig == NULL)
  {
    errno = ENOENT;
    exit (errno);
  }

  fputs (tmp, data->dhcpdconfig);

  free (tmp);
}

void
getGateway (struct variable *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);

  strncpy (data->gateway, getInput(), (size_t)MAX_LEN);

  sprintf (tmp, "option routers ");
  sprintf (tmp, data->gateway);
  sprintf (tmp, ";");

  data->dhcpdconfig = fopen (data->configLoc, "w");

  if (data->dhcpdconfig == NULL)
  {
    errno = ENOENT;
    exit (errno);
  }

  fputs (tmp, data->dhcpdconfig);

  free (tmp);
}

void
getDNS (struct variable *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);

  strncpy (data->dns, getInput(), (size_t)MAX_LEN);

  sprintf (tmp, "option domain-name-servers ");
  sprintf (tmp, data->dns);
  sprintf (tmp, ";");
  sprintf (tmp, " }");

  data->dhcpdconfig = fopen (data->configLoc, "w");

  if (data->dhcpdconfig == NULL)
  {
    errno = ENOENT;
    exit (errno);
  }

  fputs (tmp, data->dhcpdconfig);

  free (tmp);
}

void
setLoc (struct  variable *data)
{
  sprintf (data->configLoc, "/etc/dhcp/dhcpd.conf");
}

void
freeMem (struct  variable *data)
{
  free (data->subnet);
  free (data->netmask);
  free (data->rangeUp);
  free (data->rangeDown);
  free (data->gateway);
  free (data->dns);
  free (data->configLoc);
}

void
closeFile (struct  variable *data)
{
  fclose (data->dhcpdconfig);
}
