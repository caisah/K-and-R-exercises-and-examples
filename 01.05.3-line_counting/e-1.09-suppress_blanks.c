/* Write a program to copy its imput to its output, replacing each string
   of one or more blanks by a single blank. */
#include <stdio.h>

int main(void)
{
  int ch, prev;

  prev = 1;
  while ((ch=getchar()) != EOF)
    if (ch == ' ')
      {
	if (prev != ' ')
	  putchar(ch);
	prev = ch;
      }
    else
      {
	putchar(ch);
	prev = ch;
      }
  
  return 0;
}
