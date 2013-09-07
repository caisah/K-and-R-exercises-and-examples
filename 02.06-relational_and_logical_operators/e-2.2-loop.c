/* Write a loop equivalent to the for loop above without using && or ||. */
#include <stdio.h>

int main(void)
{
  int i = 0, lim = 10, c;
  char s[10];

  while((c=getchar()) != EOF)
    if (c != '\n')
      if (i < lim-1)
	{
	  s[i] = c;
	  ++i;
	}
  printf("%s\n", s);
  return 0;
}
