/**
 * @file dhcpd_conf.c
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief config the dhcp server with user data.
 * @version 0.1.0
 * @date 21 Oct 2021
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "dhcpd_conf.h"
#include "secureInput.h"

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

void
getSubnet (struct variable *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);

  getWord (data->subnet); /*TODO its wrong*/

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

  getWord (data->netmask); /*TODO its wrong*/

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

  getWord (data->rangeUp); /*TODO its wrong*/
  getWord (data->rangeDown); /*TODO its wrong*/

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

  getWord (data->gateway); /*TODO its wrong*/

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

  getWord (data->dns); /*TODO its wrong*/

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
