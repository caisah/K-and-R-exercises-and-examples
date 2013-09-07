/* Write a function strrindex(s,t), which returns the position of the rightmost 
   occurence of t in s, or -1 if there is none.*/
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000   // maximum input line length

int getline(char line[], int max);
int strrindex(char source[], char char_to_find);

char ch = 'x';   // pattern to search

/* find all lines matching pattern */
int main(void)
{
  char line[MAXLINE];

  while (getline(line, MAXLINE) > 0)
    printf("%d\n", strrindex(line, ch));
    
  return 0;
}

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
  int c, i;

  i = 0;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}

/* strindex: return index of t in s, -1 if none */
int strrindex(char s[], char c)
{
  int i;

  for (i = strlen(s)-1; (s[i] != c) && (i >= 0); i--)
    ;
  
  return (i) ? i : -1;
}
