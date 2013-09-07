#include <stdio.h>

void swap(int v[], int i, int j);
void qsort(int v[], int left, int right);

int main(void)
{
  int v[] = {3, 10, 39, 3, 49, 13, 99, 4, 11, 1, 0, -3};
  int i;

  qsort(v, 0, 11);
  for (i = 0; i <= 11; i++)
    printf("%d ", v[i]);
  
  return 0;
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right)
{
  int i, last;

  if (left >= right)
    return;         // do nothing if array contains less than two elements
  swap(v, left, (left+right)/2); // move partition element to v[0]
  last = left;
  for (i = left+1; i <= right; i++)  // partition
    if (v[i] < v[left])
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

/* swap: interchage v[i] nad v[j] */
void swap(int v[], int i, int j)
{
  int temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
