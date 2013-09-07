/* Write a program to print a histogram of the lengths of words in its input.
   It is easy to draw the histogram with the bars horizontal; a vertical
   orientation is more challenging. */
#include <stdio.h>

#define MAXLEN 20

int main(void)
{
  int c, i, j;
  int a[MAXLEN];

  for (i = 0; i <= MAXLEN; ++i)
    a[i] = 0;
  i = 0;
  
  while ((c = getchar()) != EOF)
    if ((c == ' ') || (c == '\n') || (c == '\t'))
      {
	++a[i];
	i = 0;
      }
    else
      ++i;
  
  printf("Horizontal Histogram:\n\n");
  for (i = MAXLEN; i >= 1; --i)
    {
      printf("%2d let w |",i);
      for (j = 0; j < a[i]; ++j)
	printf("_");
      printf("\n");
    }
  printf("         |");
  for (i = 7; i <= 60; ++i)
    printf("_");
  printf("\n          Number of words\n");
  
  return 0;
}
