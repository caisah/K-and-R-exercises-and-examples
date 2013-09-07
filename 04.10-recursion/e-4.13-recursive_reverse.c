/* Write a recursive version of the function reverse(s), which reverses the 
   string s in place. */
#include <stdio.h>
#include <string.h>

#define MAXLEN 100

void reverse(char s[]);

int main(void)
{
  char s[] = "abcdef";

  reverse(s);
  printf("%s\n", s);
  return 0;
}

void reverse(char s[])
{
  static int i = 0;
  int temp;

  temp = s[strlen(s)-i-1];
  s[strlen(s)-i-1] = s[i];
  s[i] = temp;
  if (i++ < (strlen(s)/2))
    reverse(s);
}
