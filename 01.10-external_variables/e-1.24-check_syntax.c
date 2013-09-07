/* Write a program to check a C program for rudimentary syntax errors like
   unbabanced parentheses, brakets and braces. Don't forget about quotes, both 
   single and double, escape sequences, and comments. (This program is hard
   if you do it in full generality.) */
#include <stdio.h>

#define MAXLINE 1000 /* max input line size */
char line[MAXLINE];  /*current input line*/

int getline(void);  /* taken from the KnR book. */

int main(void)
{
  int len=0;
  int t=0;
  int brace=0, bracket=0, parenthesis=0;
  int s_quote=1, d_quote=1;


  while ((len = getline()) > 0 )
    {
      t=0;
      while(t < len)
	{
	  if( line[t] == '[')
	    {
	      brace++;
	    }
	  if( line[t] == ']')
	    {
	      brace--;
	    }
	  if( line[t] == '(')
	    {
	      parenthesis++;
	    }
	  if( line[t] == ')')
	    {
	      parenthesis--;
	    }
	  if( line[t] == '\'')
	    {
	      s_quote *= -1;
	    }
	  if( line[t] == '"')
	    {
	      d_quote *= -1;
	    }
	  t++;
	}
    }
  if(d_quote !=1)
    printf ("Mismatching double quote mark\n");
  if(s_quote !=1)
    printf ("Mismatching single quote mark\n");
  if(parenthesis != 0)
    printf ("Mismatching parenthesis\n");
  if(brace != 0)
    printf ("Mismatching brace mark\n");
  if(bracket != 0)
    printf ("Mismatching bracket mark\n");
  if( bracket==0 && brace==0 && parenthesis==0 && s_quote == 1 && d_quote == 1)
        printf ("Syntax appears to be correct.\n");
  return 0;
}


/* getline: specialized version */
int getline(void)
{
  int c, i;
  extern char line[];
  
  for ( i=0;i<MAXLINE-1 && ( c=getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;
  if(c == '\n') 
    {
      line[i] = c;
      ++i;
    }
  line[i] = '\0';
  return i;

}
