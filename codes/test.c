
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void getFirstWord(char *dest, char *source, int index)
{
  char result[100];
  for (int i = 0; i < index; i++)
  {
    result[i] = source[i];
  }
  result[index] = '\0';
  strcpy(dest, result);
}
void getSecondWord(char *dest, char *source, int index, int total)
{
  char result[100];
  result[0] = ' ';
  int j = 1;
  for (int i = index; i < total; i++, j++)
  {
    result[j] = source[i];
  }
  result[j] = '\0';
  strcpy(dest, result);
}

void insertSpace(char *dest, int index, int total)
{
  char firstWord[100], secondWord[100];
  getFirstWord(firstWord, dest, index);
  getSecondWord(secondWord, dest, index, total);
  strcat(firstWord, secondWord);
  strcpy(dest, firstWord);
}

void arrangeName(char *name)
{
  int totalLetters = strlen(name);
  int currentLetter;

  for (int i = 0; i < totalLetters; i++)
  {
    currentLetter = (int)name[i];
    if (i == 0 && currentLetter > 96 && currentLetter < 123)
      name[i] = currentLetter - 32;

    if (i > 0 && currentLetter > 64 && currentLetter < 91)
    {
      insertSpace(name, i, totalLetters);
      i++;
      totalLetters++;
    }
  }
}

int main(void)
{
  char name[100] = "azAZ";

  arrangeName(name);
  printf("\nname = %s", name);
}