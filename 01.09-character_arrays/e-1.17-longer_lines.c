/* Write a program to print all input lines that are longer than 80 characters. */
#include <stdio.h>

#define MAXLINE 1000
#define LIMIT 80

int getline(char line[], int maxline);

int main(void)
{
  char c;
  char line[MAXLINE];
  int len;
  
  while((len = getline(line, MAXLINE)) > 0)
    if (len > LIMIT)
      printf("%s", line);

  return 0;
}

/* getline: reads a line into s, return length */
int getline(char s[], int lim)
{
  char c;
  int i;
  for (i = 0; ((c = getchar()) != EOF) && (c != '\n') && (i < lim); ++i)
    s[i] = c;
  if (c == '\n')
    {
      s[i] = c;
      ++i;
    }
  s[i] = '\0';
  return i;
}
