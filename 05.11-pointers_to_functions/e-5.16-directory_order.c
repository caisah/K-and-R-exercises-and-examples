/* Add the -d ("directory order") option, which makes comparisons only on letters,
   numbers and blanks. Make sure it works in conjunction with -f .*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getline(char*, int);
char *alloc(int);
int readlines(char**, int);
void writelines(char**, int);
void quicksort(void**, int, int, int (*)(void*, void*));
int numcmp(char*, char*);
int mystrcmp(char*, char*);

#define MAXLINES 10000
#define MAXLEN 1000

char *lineptr[MAXLINES];  /* pointers to text lines */
int decreasing = 0;       /* 0 if increasing, 1 if decreasing   -r flag */
int numeric = 0;          /* 1 if numeric sort   -n flag */
int fold = 0;             /* 1 if not case-sensitive   -f flag */
int directory = 0;        /* 1 if directory sort   -d flag */
	

int main(int argc, char* argv[])
{
  int nlines, i;
	
  while(--argc > 0) {
    ++argv;
    if((*argv)[0] == '-')
      for(i = 1; (*argv)[i]; ++i)
	switch((*argv)[i]) {
	case 'n':
	  numeric = 1;
	  break;
	case 'f':
	  fold = 1;
	  break;
	case 'r':
	  decreasing = 1;
	  break;
	case 'd':
	  directory = 1;
	  break;
	default:
	  printf("usage: sort -dfnr\n");
	  return 1;
	}
    else {
      printf("usage: sort -dfnr\n");
      return 1;
    }
  }
  if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    if(numeric)
      quicksort((void**) lineptr, 0, nlines - 1,
		(int (*)(void*, void*))numcmp);
    else
      quicksort((void**) lineptr, 0, nlines - 1,
		(int (*)(void*, void*))mystrcmp);
    writelines(lineptr, nlines);
    return 0;
  }
  else {
    printf("input too big to sort\n");
    return 1;
  }
}

/* quicksort: sort v[left]...v[right] into increasing or decreasing order */
void quicksort(void *v[], int left, int right, int (*comp)(void*, void*))
{
  int i, last;
  void swap(void *v[], int, int);
	
  if(left >= right)        /* do nothing if array contains */
    return;              /* fewer than two elements      */
  swap(v, left, (left + right) / 2);  /* move element to sort left */
  last = left;
  for(i = left + 1; i <= right; ++i) { /* move all elements < or > sort */
    if(!decreasing) {                /* element to the left according */
      if((*comp)(v[i], v[left]) < 0)  /* to order */
	swap(v, ++last, i);
    }
    else
      if((*comp)(v[i], v[left]) > 0)
	swap(v, ++last, i);
  }
  swap(v, left, last);     /* move sort element to its final position */
  quicksort(v, left, last - 1, comp);  /* sort left subarray */
  quicksort(v, last + 1, right, comp); /* sort right subarray */
}

/*
 * mystrcmp:  Compares s1 and s2 lexicographically.  Ignores characters that
 * are not letters, numbers, or whitespace if directory flag is set.  If the
 * fold flag is set, it isn't case sensitive.
 */
int mystrcmp(char *s1, char *s2)
{
  if(directory) {
    while(!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
      ++s1;       /* ignore bad characters */
    while(!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
      ++s2;       /* ignore bad characters */
  }
  while(fold ? (tolower(*s1) == tolower(*s2)) : (*s1 == *s2)) {
    if(*s1 == '\0')
      return 0;
    ++s1;
    ++s2;
    if(directory) {
      while(!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
	++s1;       /* ignore bad characters */
      while(!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
	++s2;       /* ignore bad characters */
    }
  }
  return fold ? (tolower(*s1) - tolower(*s2)) : (*s1 - *s2);
}

/*numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
  double v1, v2;
	
  v1 = atof(s1);
  v2 = atof(s2);
  if(v1 < v2)
    return -1;
  else if(v1 > v2)
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

/*readlines:  read input lines.  This version is slightly modified to read
  longer lines than the limit set by MAXLEN. */
int readlines(char *lineptr[], int maxlines)
{
  int len, nlines = 0;
  char *p, line[MAXLEN];
  int longline = 0;
	
  while((len = getline(line, MAXLEN)) > 0) {
    if(nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      if(line[len - 1] == '\n') {
	line[len - 1] = '\0';  /* delete newline */
	strcpy(p, line);
	if(!longline)
	  lineptr[nlines++] = p;
	else
	  longline = 0;
      }
      else {
	strcpy(p, line);
	if(!longline) {
	  lineptr[nlines++] = p;
	  longline = 1;
	}
      }
    }
  }
  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  while(nlines-- > 0)
    printf("%s\n", *lineptr++);
  return;
}

int getline(char *s, int max)
{
  int c;
  char *ps = s;
  while(--max && (c=getchar()) != EOF && c != '\n')
    *s++ = c;
  if(c == '\n')
    *s++ = '\n';
  *s = '\0';
  return s - ps;
}

#define ALLOCSIZE 2000000

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;    /* next free position */

char *alloc(int n)
{
  if(allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
    allocp += n;
    return allocp - n;           /* old p */
  }
  else                 /* not enough room */
    return 0;
}
