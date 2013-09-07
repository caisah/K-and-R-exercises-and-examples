#include <stdio.h>

#define MAXLEN 100

void shellsort(int v[], int n);

int main(void)
{
  int v[MAXLEN], n, i;

  printf("Enter the number of elements: ");
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%d", &v[i]);
  shellsort(v, n);
  for (i = 0; i < n; i++)
    printf("%d ", v[i]);
  printf("\n");
  return 0;
}

/* shellsort: sort v[0]...v[n-1] into increasing order. */
void shellsort(int v[], int n)
{
  int i, j, gap, temp;

  for(gap = n/2; gap > 0; gap /= 2)
    for (i = gap; i < n; i++)
      for (j = i-gap; (j>=0 && v[j]>v[j+gap]); j-=gap)
	{
	  temp = v[j];
	  v[j] = v[j+gap];
	  v[j+gap] = temp;
	}
}
