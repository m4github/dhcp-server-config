/**
 * @file srcureInput.h
 * @author Mohadeseh_Forghani (m4ghaniofficial@gmail.com)
 * @brief It is how to take all type of characters as input in C .By using "getline" function inputs are more secure.
 * @version 0.1.0
 * @date 25 jul 2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "secureInput.h"

#define MAX_LEN 64

void
initMemory (struct input *data)
{

  data->word = (char *) malloc (sizeof (char) * MAX_LEN);

  MALLOC_AND_ERRCHECK (data->word, MAX_LEN);

  data->sentence = (char *)malloc (sizeof (char) * MAX_LEN);

  MALLOC_AND_ERRCHECK (data->sentence, MAX_LEN);

}

void
getCharacter (struct input *data)
{
  char *tmp = (char *)malloc (sizeof (char));

  MALLOC_AND_ERRCHECK (tmp, sizeof (char));

  size_t size = sizeof (tmp);

  getline (&tmp, &size, stdin);

  tmp[strlen (tmp) - 1] = '\0';

  data->character = tmp[0];

  free (tmp);
}

void
getWord (struct input *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);

  MALLOC_AND_ERRCHECK (tmp, MAX_LEN);

  size_t size = sizeof (tmp);

  getline (&tmp, &size, stdin);

  tmp[strlen (tmp) - 1] = '\0';

  tmp = strtok (tmp, " ");

  if (!tmp)

    tmp = (char *)malloc (sizeof (char) * MAX_LEN);

  MALLOC_AND_ERRCHECK (tmp, MAX_LEN);

  strncpy (data->word, tmp, (size_t)MAX_LEN);

  free (tmp);
}

void
getSentence (struct input *data)
{
  char *tmp = (char *)malloc (sizeof (char) * MAX_LEN);

  MALLOC_AND_ERRCHECK (tmp, MAX_LEN);

  size_t size = sizeof (tmp);

  getline (&tmp, &size, stdin);

  tmp[strlen (tmp) - 1] = '\0';


  strncpy (data->sentence, tmp, (size_t)MAX_LEN);

  free (tmp);
}

void
cleanData (struct input *data)
{
  data->character = '\0';

  free (data->word);

  free (data->sentence);
}

