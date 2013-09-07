#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getline(char *s, int lim);

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
  char line[MAXLINE];
  int found = 0;

  if (argc != 2)
    printf("Usage: find pattern\n");
  else
    while (getline(line, MAXLINE) > 0)
      if (strstr(line, argv[1]) != NULL)
	{
	  printf("%s", line);
	  found++;
	}
  return found;
}

/* getline: get line into s, return length */
int getline(char *s, int lim)
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
