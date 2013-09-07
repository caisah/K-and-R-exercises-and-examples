/* Write a program to copy its input to its output, replacing each tab
   by \t, each backspace by \b, and each backslash by \\. */
#include <stdio.h>

int main(void)
{
  int ch;

  while((ch=getchar()) != EOF)
    if (ch == '\t')
      printf("\\t");
    else if (ch == '\b')
      printf("\\b");
    else if (ch == '\\')
      printf("\\\\");
    else
      putchar(ch);

  return 0;
}
