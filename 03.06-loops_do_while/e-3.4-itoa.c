/*In a two's complement number rerpresentation, our version of itoa does not 
  handle the largest negative number, that is the value fo n equal to (-2 to 
  the power wordsize-1). Modify it to print that value correctly, regardless of
  the machine on which it runs.*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

  sign = n;
  n = abs(n);          // sets n to be positive
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
