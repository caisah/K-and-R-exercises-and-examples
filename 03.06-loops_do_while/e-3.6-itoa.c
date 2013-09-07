/* Write a version of itoa that accepts three arguments instead of two. The third
   argument is the minimum field witdh; the converted number must be padded with 
   blanks on the left if necessary to make it wide enough.*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 100

void itoa(int n, char s[], int witdth);
void reverse(char s[]);
  
int main()
{
  int n=324;
  char s[MAXLEN];

  itoa(n, s, 6);
  printf("%s\n", s);
  
  return 0;
}

/* itoa: convert n to a string s padded if necessary */
void itoa(int n, char s[], int width)
{
  int i, sign;

  sign = n;
  n = abs(n);            // sets n to be positive
  i = 0;
  do {                   // generate digits in reverse order      
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  for (;i < width; i++)  // add padding
    s[i] = ' ';
  s[i+1] = '\0';
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
