/* Write a function invert(x,p,n) that returns x with the n bits that begin at position
   p inverted (i.e. 1 changed into 0 and vice versa, leaving the others unchanged. */
#include <stdio.h>

int invert(int x, int p, int n);

int main(void)
{
  int x, p, n;
  
  printf("Enter x: ");
  scanf("%d", &x);
  printf("Enter position p: ");
  scanf("%d", &p);
  printf("Enter number of bits n: ");
  scanf("%d", &n);
  printf("The processed number is: %d\n", invert(x, p, n));
  return 0;
}

int invert(int x, int p, int n)
{
  int ref = 0;

  ref = ~ref << n;
  ref = ~ref << p;  // mark the exact bits that need negation
  
  return ((~ref & x) | (ref & ~x));
}
