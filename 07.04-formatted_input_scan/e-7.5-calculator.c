/* Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do
   do the input and number conversion. */
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

int main(void)
{
  double sum, atof(char s[]);
  char s[MAXLINE];
  int x;
  
  sum = 0;
  while (scanf("%s", s) != EOF)
    printf("\t%g\n", sum += atof(s));
  return 0;
}

/* atof: convert string s to double */
double atof(char s[])
{
  double val, power;
  int i, sign;

  for (i = 0; s[i] == ' '; i++)   // skip white space
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if ((s[i] == '+') || (s[i] == '-'))
    i++;
  for (val = 0.0; isdigit(s[i]); i++)
    val = val * 10.0 + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]); i++)
    {
      val = 10.0 * val + (s[i] - '0');
      power *= 10.0;
    }
  return (sign * val / power);
}
