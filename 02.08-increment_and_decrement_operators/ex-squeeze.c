#include <stdio.h>

void squeeze(char s[], char ch);

int main(void)
{
  char s[] = "string";
  char c = 'n';

  squeeze(s, c);
  printf("The new string: %s\n", s);
  return 0;
}

/* squeeze: delete all c from s */
void squeeze(char s[], char c)
{
  int i, j;

  for (i = j = 0; s[i] != '\0'; i++)
    if (s[i] != c)
      s[j++] = s[i];

  s[j] = '\0';
  
}
