/* Rewrite the function lower, which converts upper case letters to lower case, 
   with a conditional expression instead of if-else. */
#include <stdio.h>

int lower(int ch);

int main(void)
{
  char s[] = "lsk L";
  int i;

  for (i = 0; s[i] != '\0'; i++)
    putchar(lower(s[i]));
  printf("\n");
}

int lower(int c)
{
  return ((c <= 'Z') && (c >= 'A')) ? (c + 32) : c;
}
