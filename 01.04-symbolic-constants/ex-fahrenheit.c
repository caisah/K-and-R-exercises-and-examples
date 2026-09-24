/* Print Fahrenheit-Celsius table; using symbolic constants. */
#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main(void)
{
  int fahr;float cels;
    
  for(fahr = LOWER; fahr <= UPPER; fahr += STEP) {
  cels=(5.0/9.0)*(fahr-32); 
                                                 
    printf("Farenheit: %3d Celsius: %6.1f\n", fahr,cels);
  }
  return 0;
}
