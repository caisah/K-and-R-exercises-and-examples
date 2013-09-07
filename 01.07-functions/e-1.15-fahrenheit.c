/* Rewrite the temperature conversion program of Section 1.2 to 
   use a function. */
#include <stdio.h>

float fahrenheit(int c);

int main(void)
{
  int i;

  for (i = 0; i <= 300; i+=20)
    printf("%3d %6.1f\n", i, fahrenheit(i));

  return 0;
}

float fahrenheit(int c)
{
  return ((5.0/9.0)*(c-32));
}
