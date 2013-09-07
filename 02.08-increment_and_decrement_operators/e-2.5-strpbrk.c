/* Write the function any(s1, s2), which returns the first location in the string 
   s1 where any character form the string s2 occurs, or -1 if s1 contains no characters
   from s2. */
#include <stdio.h>

#define MAXLEN 20

int any(char s1[], char s2[]);

int main(void)
{
  char s1[MAXLEN], s2[MAXLEN];

  printf("Enter the string: ");
  scanf("%s", s1);
  printf("Enter the matching string: ");
  scanf("%s", s2);
  printf("The first position is:  %d\n", any(s1, s2));
    
  return 0;
}

int any(char s[], char m[])
{
  int i, j;
  for (i = 0; s[i] != '\0'; ++i)
    for (j = 0; m[j] != '\0'; ++j)
      if (s[i] == m[j])
	return i;
  return -1;
}
