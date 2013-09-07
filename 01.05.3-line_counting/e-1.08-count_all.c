/* Write a program to count blanks, tabs and newlines */
#include <stdio.h>

int main(void)
{
  int blanks, tabs, newlines, ch;

  blanks = 0;
  tabs = 0;
  newlines = 0;
  while ((ch=getchar()) != EOF)
    if (ch == ' ')
      ++blanks;
    else if (ch == '\n')
      ++newlines;
    else if (ch == '\t')
      ++tabs;
  printf("Blanks: %d\nLines: %d\nTabs: %d\n", blanks, newlines, tabs);
	
  return 0;
}
