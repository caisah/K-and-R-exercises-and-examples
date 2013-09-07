#include <stdio.h>

int main(void)
{
  char s[] = "This is a string";

  printf("The length of the string is: %d", str_len(s));
  return 0;
}

/* strlen: return length of s */
int str_len(char s[])
{
  int i;

  i = 0;
  while (s[i] != '\0')
    ++i;
  return i;
}
