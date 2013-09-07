/* Extend atof to handle scientific notation of the form 123.45e-6, where a floating
   point number may be followed by e or E and optionally signed exponent. */
#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

int main(void)
{
  char s[] = "123.45e6";
  double n;

  n = atof(s);
  printf("%lf\n", n);
  return 0;
}

/* atof: convert string s to double */
double atof(char s[])
{
  double val, power;
  int i, sign, e;

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
  if ((s[i] == 'e' || s[i] == 'E') && s[i+1] == '-')
    {
      i +=2;
      e = 0;
      for (;isdigit(s[i]); i++)
	e = e * 10 + (s[i] - '0');
      for (i = 0; i <= e; i++)
	power *= 10.0;
    }
  return (sign * val / power);
}
