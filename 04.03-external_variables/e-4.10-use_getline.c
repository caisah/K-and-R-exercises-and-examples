/* An alternate organization uses getline to read an entire input line; this makes
   getch and ungetch unnecessary. Revise the caluculator to use this approach. */
#include <stdio.h>
#include <stdlib.h>  // for atof()

#define MAXOP 100    // max size of operand or operator
#define NUMBER '0'   // signal that a number was found
#define MAXLINE 1000 // length of a maximum line to be read

int getline(char [], int);
void push (double);
double pop (void);
int getop(char [], char[]);

/* reverse Polish calculator */
int main(void)
{
  int type, i;
  double op2;
  char s[MAXOP], line[MAXLINE];
  
  while (getline(line, MAXLINE) > 0) 
    while ((type = getop(s, line)) != '\0')
      switch (type)
	{
	case NUMBER:
	  push(atof(s));
	  break;
	case '+':
	  push(pop() + pop());
	  break;
	case '-':
	  op2 = pop();
	  push(pop() - op2);
	  break;
	case '*':
	  push (pop() * pop());
	  break;
	case '/':
	  op2 = pop();
	  if (op2 != 0.0)
	    push (pop() / op2);
	  break;
	case '\n':
	  printf("\t%.8g\n", pop());
	  break;
	default:
	  printf("error: unknown command %s\n", s);
	  break;
	}
  return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, con't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else
    {
      printf("error: stack empty\n");
      return 0.0;
    }
}

int getline(char s[], int lim)
{
  int c, i;

  i = 0;
  while(--lim > 0 && ((c=getchar()) != EOF && c != '\n'))
    s[i++] = c;
  if (c == '\n')
    s[i++] = '\n';
  s[i] = '\0';
  return i;              
}
 
#include <ctype.h>

int j = 0;
/* getop: get next operator or numberic operand */
int getop(char s[], char line[])
{
  int c, i;

  if (line[j] == '\n')
    {
      j++;
      return '\n';
    }
  while (((s[0] = c = line[j++]) != '\0') && (((c == ' ') || (c == '\t'))))
    printf("space");
  s[1] = '\0';
  if (c == '\0')
    {
      j = 0;
      return c;
    }
  if (!isdigit(c) && c != '.')
    return c;                  // not a number
  i = 0;
  if (isdigit(c))              // collect integer part
    while (isdigit(s[++i] = c = line[j++]))
      ;
  if (c == '.')                // collect fraction part
    while (isdigit(s[++i] = c = line[j++]))
      ;
  s[i] = '\0';
  
  return NUMBER;
}
