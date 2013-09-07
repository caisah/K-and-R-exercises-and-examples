/* Write a program to determine the ranges of char, short, int, and long variables,
   both signed and unsigned, by printing the appripriate values from standard
   headers and by direct computation. */
#include <stdio.h>

int main(void)
{
  printf("char: %d\n", sizeof(char));
  printf("short: %d\n", sizeof(short));
  printf("int: %d\n", sizeof(int));
  printf("unsigned int: %d\n", sizeof(unsigned int));
  printf("signed int: %d\n", sizeof(signed int));
  printf("long: %d\n", sizeof(long));

  printf("\nfloat: %d\n", sizeof(float));
  printf("double: %d\n", sizeof(double));
  printf("long double: %d\n", sizeof(long double));

  printf("\nComputed range of char: %d\n", compute_char());
  // the range for other types can be computed like this as well
  return 0;
}

/* compute_char: returns the range of a char in bytes. */
int compute_char(void)
{
  char x = 1;
  int i = 0;

  while (x)
    {
      x = x << 1;   // shift left by 1 bit
      ++i;
    }
  return (i / 8);  // transform bits in bytes
}
