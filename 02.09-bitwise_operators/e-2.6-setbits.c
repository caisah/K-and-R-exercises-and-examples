/* Write a function setbits(s,p,n,y) that returns x with the n bits that begin at
   position p set to the rightmost n bits of y, leaving the other bits unchanged. */
#include <stdio.h>

int setbits(int x, int p, int n, int y);

int main(void)
{
  int x, p, n, y;
  
  printf("Enter x: ");
  scanf("%d", &x);
  printf("Enter y: ");
  scanf("%d", &y);
  printf("Enter position p: ");
  scanf("%d", &p);
  printf("Enter number of bits n: ");
  scanf("%d", &n);
  printf("The processed number is: %d\n", setbits(x, p, n, y));
  return 0;
}

int setbits(int x, int p, int n, int y)
{
  y = y >> (p-1);      // move the bits starting at pos p to the end
  y = y & ~(~0 << n);  // null all the bits from a pos higher than n
  x = x & (~0 << n);   // null the last n bits
  return (x | y);
}
