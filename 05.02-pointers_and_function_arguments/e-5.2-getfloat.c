/* As written, getint treats a + or - not followed by a digit as a valid representation
   of zero. Fix it to push such a character back to the input. */
#include <stdio.h>

#define MAXLEN 1000

int getint(float *);

int main(void)
{
  float a[MAXLEN];
  int n;

  for (n = 0; n < MAXLEN && getint(&a[n]) != EOF; n++)
    ;
  printf("\n");
  for (int i = 0; i < n; i++)
    printf("%g ", a[i]);
  printf("\n");
  return 0;
}

#include <ctype.h>
#include <math.h>

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(float *pn)
{
  int c, sign, prev = 0, j;
  float inte, frac;

  while (isspace(c = getch())) // skip whitespaces
    ;
  if (!isdigit(c) && c != EOF && c!= '+' && c != '-')
    ungetch(c);   // it's not a number
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  for (inte = 0; isdigit(c); c = getch())
    inte = 10.0 * inte + (float) (c - '0');
  if (c == '.')
    {
      c = getch();
      for (frac = 0, j = 0; isdigit(c); c = getch(), j++)
	frac = 10.0 * frac + (float) (c - '0');
    }
  *pn = ((float) sign) * (inte + frac/powf(10, j));
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


