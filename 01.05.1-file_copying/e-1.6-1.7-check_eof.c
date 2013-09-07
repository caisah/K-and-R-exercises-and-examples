/* verifies EOF and prints the value of EOF*/
#include <stdio.h>

int main(void)
{
  printf("The valut of getchar() != EOF is: %d\n", (getchar() != EOF));

  printf("\nThe value of EOF is: %d\n", EOF);

  return 0;
}
