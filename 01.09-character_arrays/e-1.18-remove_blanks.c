/* Write a program to remove trailing blanks and tabs from each line
   of input, and to delete entirely blank lines. */
#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int limit);
void print_line(char line[], int line_length);
int is_blank(char line[]);

int main(void)
{
  int len;
  char line[MAXLINE];
  
  while ((len = getline(line, MAXLINE)) > 0)
    print_line(line, len);
 
  return 0;
}

int getline(char s[], int lim)
{
  int c, i;

  for (i = 0; (i < lim-1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
    s[i] = c;
  if (c == '\n')
    {
      s[i] = c;
      ++i;
    }
  s[i] = '\0';
  return i;
}

/* print_line: prints a formated line - no trailing blanks, tabs or empty lines */
void print_line(char l[], int len)
{
  int i, j;

  if (is_blank(l))                                   // exit if blank line
    return;
  for (i = len-2; (l[j] == ' ') && (i >= 0); --i)    // remove all trailing blanks
    l[i] = '\0';
  if  (i < len-2)                                    // if there were blanks add \n to the string
    l[i+1] = '\n';
  for(j = 0; l[j] != '\0'; ++j)                      // print all character that are not tabs
    if (l[j] != '\t')
      putchar(l[j]);
}

/* returns 1 if line is blank and 0 otherwise */
int is_blank(char l[])
{
  int i;
  
  if (l[0] == '\n')
    return 1;
  for(i = 0; l[i] != '\n'; ++i)
    if ((l[i] != ' ') && (l[i] != '\t'))
      return 0;
  return 1;
}
