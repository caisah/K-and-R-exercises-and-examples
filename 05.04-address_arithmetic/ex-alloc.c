#include <stdio.h>

char *alloc(int);
void afree(char *);

int main()
{
  int n = 10;
  char *p;

  p = alloc(n);
  if (p)
    printf("Allocated 4*%d bytes", n);
  else
    printf("Could not allocate!");

  p = p - 3;
  afree(p);
  
  return 0;
}

#define ALLOCSIZE 10000 // size of available space

static char allocbuf[ALLOCSIZE];   // storage for alloc
static char *allocp = allocbuf;   // next free

char *alloc(int n) // return pointter to n characters
{
  if (allocbuf + ALLOCSIZE - allocp >= n)  // it fits
    {
      allocp += n;
      return allocp - n;         // old p
    }
  else                           // not enough room
    return 0;
}

void afree(char *p)              // free storage pointed to by p
{
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}
