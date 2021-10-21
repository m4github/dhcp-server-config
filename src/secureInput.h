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

#if !defined(_SECURE_INPUT_H)
#define _SECURE_INPUT_H
#define getStdin(x,size) getline(x,size,stdin);
#define MALLOC_AND_ERRCHECK(var, n)   if(var == NULL && n > 0) \
  { \
    fprintf(stderr, "Couldn't allocate memory\n"); \
    exit(EXIT_FAILURE); \
  } \


struct input
{
    char character;

    char *word;

    char *sentence;
};
 
void initMemory(struct input *data);

void getCharacter(struct input *data);

void getWord(struct input *data);

void getSentence(struct input *data);

void cleanData(struct input *data);

#endif
