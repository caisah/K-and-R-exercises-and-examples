/* Write the function htoi(s), which converts a string of hexadecimal digits
   (including an optional 0x or 0X) into its equivalent integer value. The
   allowable digits are 0 through 9, a through f and A through F. */
#include <stdio.h>
#include <ctype.h>

#define BASE 16

int htoi(char str[]);

int main(void)
{
  char s[] = "0x1yf";

  printf("Hex string converted: %d\n", htoi(s));

  return 0;
}

/* htoi: returns the integer equivalent of a hex string */
int htoi(char s[])
{
  int i, j, m, num = 0;
  char ch[] = "0123456789abcdef"; // a map string
  
  if ((s[0] == '0')  && ((s[1] == 'x') || (s[1]) == 'X'))
    m = 2;
  else
    m = 0;
  for (i = m; s[i] != '\0'; ++i)
    for (j = 0; j <= BASE; ++j)
      {
	if (tolower(s[i]) == ch[j])
	{
	  num = num * 16 + j;
	  break;
	}
	if (j == BASE)
	  return num;
      }
  return num;
}
