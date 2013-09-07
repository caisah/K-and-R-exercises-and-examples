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
  high = n - 1;
  while (low <= high)
    {
      mid = (low + high) / 2;
      if (x < v[mid])
	high = mid - 1;
      else if (x > v[mid])
	low = mid + 1;
      else               // found match
	return mid;
    }
  return -1;
}
