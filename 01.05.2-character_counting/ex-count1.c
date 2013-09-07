/* count characters in input; 1st version */
#include <stdio.h>

int main(void)
{
  long nc;

  nc = 0;
  while (getchar() != EOF)
    ++nc;
  printf("%ld\n", nc);

  return 0;
}
