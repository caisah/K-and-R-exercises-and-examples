/* Write a program entab that replaces strings of blanks by the minimum number of tabs
   and blanks to achieve the same spacing. Use the same tab stops as for detab. */
#include <stdio.h>

#define TABLEN 3
#define MAXLINE 1000

int getline(char line[], int limit);
void print_detab(char line[]);
int tabs_to_insert_in(char lint[], int position);

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
  int i;
  char c;

  for (i = 0; (i < lim-1) && ((c = getchar()) != EOF) && c != '\n'; ++i)
    l[i] = c;
  if (c == '\n')
    {
      l[i] = c;
      ++i;
    }
  l[i] = '\0';
  return i;
}

/* print_detab: prints the string line with tabs instead of blanks */
void print_detab(char s[])
{
  int i, j, tabs;

  i = 0;
  while (s[i] != '\0')
    if ((s[i] == ' ') && (tabs = tabs_to_insert_in(s, i)))         // if char is space
      for (j = 1; j <= tabs; ++j)   // and can insert tabs in string instead of spaces
	{
	  putchar('\t');
	  i += TABLEN;          // jump pass the spaces transformed in tabs
	}
    else
      {
	putchar(s[i]);
	++i;
      }
}

/* tabs_to_insert: returns the number of tabs that can replace spaces */
int tabs_to_insert_in(char s[], int n)
{
  int i, j;

  j = 0;
  for (i = n; (s[i] != '\n') && (s[i] == ' '); ++i)
    ++j;
  if (j >= TABLEN)
    return (j / TABLEN);
  else
    return 0;
}
