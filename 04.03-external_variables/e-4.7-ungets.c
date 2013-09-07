/* Write a routine ungets(s) that will push back an entire string onto the input.
   Should ungets know about buf and bufp or shoild it just use ungetch? */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]);
int getch(void);
void ungetch(int c);
void ungets(char s[]);

int main(void)
{
  int type;
  char s[MAXOP];

  while ((type = getop(s)) != EOF)
    printf("%c", type);
  return 0;
}
#include <ctype.h>

int getch(void);
void ingetch(int);

/* getop: get next operator or numberic operand */
int getop(char s[])
{
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c;                  // not a number
  i = 0;
  if (isdigit(c))              // collect integer part
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')                // collect fraction part
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

#define BUFFSIZE 100

char buf[BUFFSIZE];  // buffer for ungetch
int bufp = 0;        // next free posotion in buf

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

void ungets(char s[])
{
  int i = strlen(s);
  
  while (i>0)
    ungetch(s[--i]);
}

