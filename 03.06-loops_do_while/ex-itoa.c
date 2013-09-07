#include <stdio.h>
#include <string.h>

#define MAXLEN 100

void itoa(int n, char s[]);
void reverse(char s[]);
  
int main()
{
  int n=324;
  char s[MAXLEN];

  itoa(n, s);
  printf("%s\n", s);
  
  return 0;
}

/* itoa: convert n to characters on s */
void itoa(int n, char s[])
{
  int i, sign;

  if ((sign = n) < 0)  // record sign
    n = -n;            // make n positive
  i = 0;
  do {                 // generate digits in reverse order      
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

void reverse(char s[])
{
  int i, j;
  char c;
  
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
      c = s[i];
      s[i] = s[j];
      s[j] = c;
    }
}
