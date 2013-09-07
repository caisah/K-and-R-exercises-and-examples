/* Write a pointer version of the function strcat that we showed in Chapter 2:
   strcat(s,t) copies the string t to the end of s. */
#include <stdio.h>

void str_cat(char *, char *);

int main(void)
{
  
  char *s1, *s2;
  char s3 [] = "first",  s4[] = "second";

  s1 = s3;
  s2 = s4;
  str_cat(s1, s2);
  printf("Concatenated string: %s", s1);
  return 0;
}

void str_cat(char *s, char *t)
{
  for (;*s != '\0';s++)
    ;
  while ((*s++ = *t++) != '\0')
    ;
}
