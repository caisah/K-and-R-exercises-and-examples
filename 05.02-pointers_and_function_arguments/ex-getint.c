#include <stdio.h>

#define MAXLEN 1000

int getint(int *);

int main(void)
{
  int a[MAXLEN], n;

  for (n = 0; n < MAXLEN && getint(&a[n]) != EOF; n++)
    ;
  printf("\n");
  printf("%d", a[0]);
  for (int i = 1; i < n; i++)
    printf("%d ", a[i]);
  printf("\n");
  return 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
  int c, sign;

  while (isspace(c = getch())) // skip whitespaces
    ;
  if (!isdigit(c) && c != EOF && c!= '+' && c != '-')
    {
      ungetch(c);   // it's not a number
      return 0;
    }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

#define BUFFSIZE 100

char buf[BUFFSIZE];  // buffer for ungetch
int bufp = 0;        // next free position in buf

int getch(void)      // get a (possibly pushed back) character
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  // push back on input
{
  if (bufp >= BUFFSIZE)
    printf("ungetch: too many characters\n");
  else buf[bufp++] = c;
}


