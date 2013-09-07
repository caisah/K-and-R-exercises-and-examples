/* Write an alternate version of squeeze(s1, s2), that deletes each character
   in s1 that matches any character in the string s2. */
#include <stdio.h>

#define MAXLEN 20

void squeeze(char s1[], char s2[]);

int main(void)
{
  char s1[MAXLEN], s2[MAXLEN];

  printf("Enter the string: ");
  scanf("%s", s1);
  printf("Enter the matching string: ");
  scanf("%s", s2);
  squeeze(s1, s2);
  printf("The sqeezed string is: %s\n", s1);
    
  return 0;
}

void squeeze(char s[], char m[])
{
  int i, j, k;

  for (i = k = 0; s[i] != '\0'; ++i)
    {
      for (j = 0; (m[j] != s[i]) && (m[j] != '\0'); ++j)
	;
      if (m[j] == '\0')
	s[k++] = s[i];
    }
  s[k] = '\0';
}
