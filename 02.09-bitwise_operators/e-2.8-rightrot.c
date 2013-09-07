/* Write a function rightrot(x,n) that returns the value of the integer x rotated
   to the right by n bit positions. */
#include <stdio.h>

int rightrot(int x, int n);

int main(void)
{
  int x, n;
  
  printf("Enter x: ");
  scanf("%d", &x);
  printf("Enter number of bits n: ");
  scanf("%d", &n);
  printf("The processed number is: %d\n", rightrot(x, n));
  return 0;
}

int rightrot(int x, int n)
{
  int end = 0;

  end = ~(~end << n);
  end = x & end;
  end = end << (8 * sizeof(x) - n);
  return ((x >> n) | end);
}
