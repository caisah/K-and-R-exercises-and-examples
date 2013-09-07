/* Write a program that will print arbitrary input in a sensible way. As a minumum, it
   should print non graphic characters in octal or hexadecimal according to local custom,
   and break long text lines. */
#include <stdio.h>

#define LINELEN 10
#define OCTLEN 3

int printoct(int, int);
int printnor(int, int);

int main(void)
{
  int c, cnum = 0;

  while ((c = getchar()) != EOF)
    {
      cnum = (c < 32) ? printoct(c, cnum) : printnor(c, cnum);
      if (cnum >= LINELEN)
	cnum = cnum - LINELEN;
    }
  return 0;
}

int printoct(int c, int n)
{
  int len;
  
  if ((len = (n + OCTLEN)) <= LINELEN)
    printf("%o", c);
  else
    printf("\n%o", c);
  return len;
}

int printnor(int c, int n)
{
  int len;

  if ((len = (n + 1)) <= LINELEN)
    printf("%c", c);
  else
    printf("\n%c", c);
  return len;
}
