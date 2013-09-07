/* count lines in input */
#include <stdio.h>

int main(void)
{
  int c, nl;

  nl = 0;
  while ((c = getchar()) != EOF)
    if (c == '\n')
      ++nl;
  printf("%d\n", nl);

  return 0;
}
