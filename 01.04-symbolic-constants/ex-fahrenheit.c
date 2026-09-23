/* Print Fahrenheit-Celsius table; using symbolic constants. */
#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main(void)
{
  int fahr;

  for(fahr = LOWER; fahr <= UPPER; fahr += STEP)  // int cels=(5/9)*(fahr-32); 
                                                  // printf("%3d %6.1f\n", fahr,cels);
    printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));

  return 0;
}
