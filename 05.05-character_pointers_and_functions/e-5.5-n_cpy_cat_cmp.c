/* Write versions of the library functions strncpy, strncat, and strncmp, which operate
   on at most the first n characters of their argument string strings. For example,
   strncpy(s,t,n) copies at most n characters of t to s. */
#include <stdio.h>

char *strn_cpy(char *dest, char *source, int n);
char *strn_cat(char *dest, char *source, int n);
int strn_cmp(char *s1, char *s2, int n);

int main(void)
{
  
  char *s1, *s2;
  char s3[] = "fiast",  s4[] = "firbalaportocala";

  s1 = s3;
  printf("%d", strn_cmp(s1, s4, 2));
  return 0;
}

char *strn_cpy(char *s, char *t, int n)
{
  int i;
  char *r;

  r = s;
  for(i = 0; i < n && *t != '\0'; i++)
    *s++ = *t++;
  *s = '\0';
  return r;
}

char *strn_cat(char *s, char *t, int n)
{
  char *r;
  int i;

  r = s;
  for (;*s != '\0'; s++)
    ;
  for(i = 0; *t != '\0' && i < n; i++)
    *s++ = *t++;
  *s = '\0';
  return r;
}

int strn_cmp(char *s, char *t, int n)
{
  int i;

  for (i = 0; i < n && (*s++ == *t++); i++)
    ;
  if (i == n)
    return 0;
  else
    return (*(s-1) > *(t-1)) ? 1 : -1;
}
