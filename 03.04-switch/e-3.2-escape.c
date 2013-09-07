/* Write a function escape(s,t) that converts characters like newline and tab into
   visible sequences like \n and \t as it copies the string t to s. Write a function
   for the other direction as well, converting escape sequences into the real characters. */
#include <stdio.h>

#define MAXLEN 100

void escape(char s[], char t[]);
void r_escape (char s[], char t[]);

int main(void)
{
  char s[MAXLEN], t[MAXLEN], u[MAXLEN], c;
  int i = 0;

  printf("Enter the string: ");
  while ((c = getchar()) != EOF)
    s[i++] = c;
  s[i] = '\0';
  escape(s, t);
  printf("\nThe escaped string: %s\n", t);
  r_escape(t, u);
  printf("The re-escaped string is: %s\n", u);
  return 0;
}

void escape (char s[], char t[])
{
  int i = 0, j = 0;
  
  while (s[i] != '\0')
    {
      switch (s[i])
	{
	case '\n':
	  t[j++] = '\\';
	  t[j++] = 'n';
	  i++;
	  break;
	case '\t':
	  t[j++] = '\\';
	  t[j++] = 't';
	  i++;
	  break;
	default:
	  t[j++] = s[i++];
	  break;
	}
    }
  t[j] = '\0';
}

void r_escape(char s[], char t[])
{
  int i = 0, j = 0;

  while (s[i] != '\0')
    if (s[i] == '\\')
      switch (s[i+1])
	{
	case 't':
	  t[j++] = '\t';
	  i+=2;
	  break;
	case 'n':
	  t[j++] = '\n';
	  i+=2;
	  break;
	}
    else
      t[j++] = s[i++];
  t[j] = '\0';
}
