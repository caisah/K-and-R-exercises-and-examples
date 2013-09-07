/* Our binary search makes two tests inside the loop, when ont would suffice 
   (at the price of more tests outside). Write a version with only one test
   inside the loop. */
#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void)
{
  int v[] = {1, 3, 4, 11, 33, 130, 132, 153, 166}; // sorted array

  printf("%d\n", binsearch(11, v, 9));
  return 0;
}

int binsearch(int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n-1;
  while ((low <= high) && (v[mid] != x))
    {
      mid = (low + high) / 2;
      if (x < v[mid])
	high = mid - 1;
      else
	low = mid + 1;
    }
  return ((v[mid] == x) ? mid : -1);
}
