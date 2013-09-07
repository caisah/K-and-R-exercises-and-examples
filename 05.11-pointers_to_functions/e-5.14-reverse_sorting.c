/* Modify the sort prgram to handle a -r flag, which indicates sorting in reverse
   (decreasing) order. Be sure that -r works with -n. */
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort2(void *lineptr[], int left, int right, int (*comp)(void *, void *), int r);

int numcmp(char *, char *);

int main(int argc, char *argv[])
{
  int nlines, i = 0, j = 1;
  int numeric = 0;
  int reversed = 0;

  if(argc > 1)
    while(++i < argc)
      {
	while (argv[i][j] != '\0')
	  switch (argv[i][j++])
	    {
	    case 'n':
	      numeric = 1;
	      break;
	    case 'r':
	      reversed = 1;
	      break;
	    }
	j = 1;
      }
  if((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
      qsort2((void **) lineptr, 0, nlines-1,
	     numeric ? (int (*)(void*, void*)) numcmp :
	     (int (*)(void*, void*)) strcmp,
	     reversed ? 1 : 0);
      writelines(lineptr, nlines);
      return 0;
    }
  else
    {
      printf("input too big to sort\n");
      return 1;
    }
}

void qsort2(void *v[], int left, int right, int(*comp)(void *, void *), int reversed)
{
  int i, last;
  void swap(void *v[], int, int);

  if(left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for(i = left + 1; i <= right; i++)
    switch (reversed)
      {
      case 0:
	if((*comp)(v[i], v[left]) < 0)
	  swap(v, ++last, i);
	break;
      case 1:
	if((*comp)(v[i], v[left]) > 0)
	  swap(v, ++last, i);
	break;
      }
  swap(v, left, last);
  qsort2(v, left, last - 1, comp, reversed);
  qsort2(v, last + 1, right, comp, reversed);
}

#include <stdlib.h>

int numcmp(char *s1, char *s2)
{
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

void swap(void *v[], int i, int j)
{
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}


#define MAXLEN 1000   // max length of any input line
int getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else
      {
	line[len-1] = '\0';   // delete newline
	strcpy(p, line);
	lineptr[nlines++] = p;
      }
  return nlines;
}

/* getline: read a line into s, return length */
int getline(char *s, int lim)
{
  int c, i;

  for (i = 0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; i++)
    s[i] = c;
  if (c == '\n')
    {
      s[i] = c;
      ++i;
    }
  s[i] = '\0';
  return i;
}

#define ALLOCSIZE 50000           // size of available space

static char allocbuf[ALLOCSIZE];  // storage for alloc
static char *allocp = allocbuf;   // next free position

char *alloc(int n)
{
  if (allocbuf + ALLOCSIZE - allocp >= n)   // if it fits
    {
      allocp += n;
      return allocp - n;
    }
  else
    return 0;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  int i;

  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

