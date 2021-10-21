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
#include "dhcpd_conf.h"
#include "secureInput.h"

#define sizeof (char) 64

void
initMem (struct  variables *data)
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

  sprintf (data->tmp, "subnet ");
  sprintf (data->tmp, data->subnet);

  data->dhcpdConfig = fopen (data->configLoc, "w");

  if (data.rootFileUID == NULL)
  {
    errno = ENOENT;
    return -1;
  }

  fputc (tmp, data->dhcpdConfig);

  free (tmp);

}

void
getnetMask (struct variable *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);
  getWord (data->netMask); /*TODO its wrong*/

  sprintf (data->tmp, " netmask ");
  sprintf (data->tmp, data->netMask);
  sprintf (data->tmp, " { ");

  data->dhcpdConfig = fopen (data->configLoc, "w");

  if (data.rootFileUID == NULL)
  {
    errno = ENOENT;
    return -1;
  }

  fputc (tmp, data->dhcpdConfig);

  free (tmp);

}

void
getRange (struct variable *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);
  getWord (data->rangeUp); /*TODO its wrong*/
  getWord (data->rangeDown); /*TODO its wrong*/

  sprintf (data->tmp, "range ");
  sprintf (data->tmp, data->rangeUp);
  sprintf (data->tmp, " ");
  sprintf (data->tmp, data->rangeDown);
  sprintf (data->tmp, ";");

  data->dhcpdConfig = fopen (data->configLoc, "w");

  if (data.rootFileUID == NULL)
  {
    errno = ENOENT;
    return -1;
  }

  fputc (tmp, data->dhcpdConfig);

  free (tmp);
}

void
getGateway (struct variable *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);
  getWord (data->gateway); /*TODO its wrong*/

  sprintf (data->tmp, "option routers ");
  sprintf (data->tmp, data->gateway);
  sprintf (data->tmp, ";");

  data->dhcpdConfig = fopen (data->configLoc, "w");

  if (data.rootFileUID == NULL)
  {
    errno = ENOENT;
    return -1;
  }

  fputc (tmp, data->dhcpdConfig);

  free (tmp);

}

void
getDNS (struct variable *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);
  getWord (data->dns); /*TODO its wrong*/

  sprintf (data->tmp, "option domain-name-servers ");
  sprintf (data->tmp, data->dns);
  sprintf (data->tmp, ";");
  sprintf (data->tmp, " }");


  data->dhcpdConfig = fopen (data->configLoc, "w");

  if (data.rootFileUID == NULL)
  {
    errno = ENOENT;
    return -1;
  }

  fputc (tmp, data->dhcpdConfig);

  free (tmp);

}

void
setLoc (struct  variables *data)
{
  sprintf (data->configLoc, "/etc/dhcp/dhcpd.conf");
}

void
freeMem (struct  variables *data)
{
  free (data->subnet);
  free (data->netmask);
  free (data->rangeUp);
  free (data->rangeDown);
  free (data->gateway);
  free (data->dns);
  free (data->configLocation);
}

void
closeFile (struct  variables *data)
{
  fclose (data->dhcpdConfig);
}