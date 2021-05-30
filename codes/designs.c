// This is are all the UI design functions used in the program.

#include <stdio.h>
#include <time.h>

#define DESIGN (70)
#define DESIGN2 (35)

//Prints the date and time together with the names of programmers
void printTime(void)
{
  printf("\n\t\tPrepared by: \n");
  printf("\t\t\tAranda, Charles\n");
  printf("\t\t\tMiclat, Mhark Angelo\n");
  printf("\t\t\tRebanal, Wyn Christian\n");
  printf("\t\t\tSedutan, Lance Lurance\n");
  printf("\t\t\tZuniga, Enrico Paul\n");
  char temp[100];
  time_t current_time = time(NULL);
  struct tm *tm = localtime(&current_time);
  strftime(temp, sizeof(temp), "%c", tm);
  printf("\n\t\tDate and Time Prepared: ");
  printf("%s\n\n", temp);

  return;
}
//Print a line of equal sign
void printEquals(void)
{
  for (int i = 0; i < DESIGN; i++)
    printf("=");
  printf("\n");

  return;
}

//Print a line of dash sign
void printDash(void)
{
  for (int i = 0; i < DESIGN; i++)
    printf("-");
  printf("\n");

  return;
}

//Print a line of asterisk sign
void printAsterisk(void)
{
  for (int i = 0; i < DESIGN; i++)
    printf("*");
  printf("\n");

  return;
}

//Print a line of slash sign
void printSlash(void)
{
  for (int i = 0; i < DESIGN2; i++)
    printf("/\\");
  printf("\n");

  return;
}