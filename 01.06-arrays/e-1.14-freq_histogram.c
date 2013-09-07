/* Write a program to print a histogram of the frequencies of different 
   characters in its input. */
#include <stdio.h>

#define ALL_CHARS 26
#define ALL_NUMS 10

int main(void)
{
  int c, i, j;
  int ch[ALL_CHARS], num[ALL_NUMS];

  for (i = 0; i < ALL_CHARS; ++i)
    ch[i] = 0;
  for (i = 0; i < ALL_NUMS; ++i)
    num[i] = 0;

  while((c=getchar()) != EOF)
    if (c >= '0')
      if (c <= '9')
	++num[c-'0'];
      else if (c >= 'A')
	if (c <= 'Z')
	  ++ch[c-'A'];
	else if (c >= 'a')
	  if (c <= 'z')
	    ++ch[c-'a'];

  printf("Horizontal Histogram:\n\n");
  for (i = ALL_CHARS-1; i >= 0; --i)
    {
      printf("%c |", ('a'+i));
      for (j = 0; j < ch[i]; ++j)
	printf("_");
      printf("\n");
    }
  for (i = ALL_NUMS-1; i >= 0; --i)
    {
      printf("%c |", ('0'+i));
      for (j = 0; j < num[i]; ++j)
	printf("_");
      printf("\n");
    }
  printf("  |");
  for (i = 7; i <= 60; ++i)
    printf("_");
  printf("\n   Frequency\n");

  return 0;
}
