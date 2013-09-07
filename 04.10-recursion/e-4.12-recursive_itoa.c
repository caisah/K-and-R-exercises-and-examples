/* Adapt the ideas of printd to write a recursive version of itoa; that is,
   convert an integer into a string by calling a recursive routine. */
#include <stdio.h>

#define MAXLEN 100

void itoa(int n, char s[]);

int main(void)
{
  int n = 234;
  char a[MAXLEN];
  
  itoa(n, a);
  printf("%s", a);
  return 0;
}

void itoa(int n, char s[])
{
  static int i = 0;

  if (n < 0)
    {
      s[i++] = '-';
      n = -n;
    }
  if ((n/10) > 0)
    itoa((n/10), s);
  s[i++] = (n % 10) + '0';
  s[i] = '\0';
}
