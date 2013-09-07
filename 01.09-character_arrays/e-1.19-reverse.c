/* Write a function reverse(s) that reverses the characte string s. 
   Use it to write a program that reverses its input a line at a time. */
#include <stdio.h>

#define MAXLINE 1000

void readstring(char s[], int limit);
void reverse(char s[]);

int main(void)
{
  char s[MAXLINE];

  printf("Enter a line:\n");
  readstring(s, MAXLINE);
  reverse(s);
  printf("String reversed: %s\n", s);

  return 0;
}


void readstring(char s[], int lim)
{
  int i, c;
  
  for (i = 0; ((c = getchar()) != EOF) && (c != '\n') && (i < (lim-1)); ++i)
    s[i] = c;
  s[i] = '\0';
}

void reverse(char s[])
{
  int i, j;
  char hold;

  if (s[0] == '\0')                  // if the string is empty, exit
    return;
  for (i = 0; s[i] != '\0'; ++i)     // move to the end of the string
    ;
  j = i - 1;
  for (i = 0; i < j; ++i)           // interchange the characters
    {
      hold = s[i];
      s[i] = s[j];
      s[j] = hold;
      --j;
    }
}
