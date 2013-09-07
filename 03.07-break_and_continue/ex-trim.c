#include <stdio.h>
#include <string.h>

#define MAXLEN 100

int trim(char s[]);

int main(void)
{
  char s[] = "this is a string  ";

  trim (s);
  printf("%s", s);
  return 0;
}

/* trim: remove trailing blanks, tabs, newlines */
int trim(char s[])
{
  int n;

  for (n = strlen(s)-1; n >= 0; n--)
    if ((s[n] != ' ') && (s[n] != '\t') && (s[n] != '\n'))
      break;
  s[n+1] = '\n';
  return n;
}
