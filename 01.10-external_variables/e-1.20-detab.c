/* Write a program detab that replaces tabs in the input with the proper number
   of blanks to space to the next tab stop. Assume a fixed set of ab stops, say 
   every n columns. */
#include <stdio.h>

#define TABLEN 5
#define MAXLINE 1000

void print_detab(char line[]);
int getline(char line[], int maxline);

int main(void)
{
  int len;
  char line[MAXLINE];

  while ((len = getline(line, MAXLINE)) > 0)
    print_detab(line);
  return 0;
}

int getline(char l[], int lim)
{
  int c, i;

  for (i = 0; (i < lim -1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
    l[i] = c;
  if (c == '\n')
    {
      l[i] = c;
      ++i;
    }
  l[i] = '\0';
  return i;
}

void print_detab(char s[])
{
  int i, j, n;

  if (s[0] == '\t')         
    for (i = 0; i < TABLEN; ++i)
      putchar(' ');                       // if the first char is tab print TABLEN spaces
  for (i = 0; (s[i] != '\0'); ++i)
    if (s[i] != '\t')
      putchar(s[i]);                      // print char if is not tab
    else if (n = (i % TABLEN))            // replace tab with appropriate no. of chars.
      for (j = 1; j <= (TABLEN - n); ++j)
	putchar(' ');
    else
      putchar(' ');
}
