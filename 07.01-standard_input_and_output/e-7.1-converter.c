/* Write a program that converts upper case to lower or lower case to upper, depending
   on the name it is invoked with as found in argv[0]. */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void printc(int (*f)(int));

int main(int argc, char *argv[])
{
  if (strcmp(argv[0], "lower") == 0)
    printc(tolower);
  if (strcmp(argv[0], "upper") == 0)
    printc(toupper);
  return 0;
}

void printc(int (*f)(int))
{
  char c;
  
  while ((c = getchar()) != EOF)
    putchar(f(c));
}
