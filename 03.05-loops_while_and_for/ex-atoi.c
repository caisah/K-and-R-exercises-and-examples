#include <stdio.h>
#include <ctype.h>

#define MAXLEN 100

int a_toi(char s[]);

int main(void)
{
  char s[MAXLEN], c;
  int i = 0;

  printf("Enter the string: ");
  while ((c = getchar()) != EOF)
    s[i++] = c;
  s[i] = '\n';
  printf("%d\n", a_toi(s));
  return 0;
}

int a_toi(char s[])
{
  int i, n, sign;

  for (i = 0; isspace(s[i]); i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if ((s[i] == '-') || (s[i] == '+'))   // skip sign
    i++;
  for (n = 0; isdigit(s[i]); i++)
    n = 10 * n + (s[i] - '0');
  return sign * n;
}
