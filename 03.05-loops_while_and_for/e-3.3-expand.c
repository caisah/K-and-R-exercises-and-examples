/* Write a function expand(s1,s2) that expands shorthand notations like a-z in the 
   string s1 into the equivalent complete lise abc...xyz in s2. Allow for letters of 
   either case and digits , and be prepared to handle cases like a-b-c and a-z0-9 
   and -a-z. Arrange that a leading or trailing - is taken literally. */
#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000

void expand(char s1[], char s2[]);

int main(void)
{
  char s1[MAXLEN], s2[MAXLEN], c;
  int i = 0;

  printf("Enter the string: ");
  while((c = getchar()) != EOF)
    s1[i++] = c;
  s1[i] = '\0';
  expand(s1, s2);
  printf("\nExpanded :\n%s\n", s2);
  return 0;
}

void expand(char s[], char t[])
{
  int i = 0, j = 0, k;

  t[j++] = s[i++];
  while (s[i] != '\0')
    if ((s[i] == '-') && (s[i+1] != '\0') &&
	((isdigit(s[i-1]) && isdigit(s[i+1])) ||
	 (isalpha(s[i-1]) && isalpha(s[i+1]))))
      {
	for (k = (s[i-1]+1); k <=s[i+1]; k++)
	  t[j++] = k;
	i+=2;
      }
    else
      t[j++] = s[i++];
  t[j] = '\0';
}
