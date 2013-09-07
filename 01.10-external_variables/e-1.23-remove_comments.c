/* Write a program to remove all comments from a C program. Don't forget to handle
   quoted strings and character constants properly. C comments do not nest. */
#include <stdio.h>

#define MAXLINE 1000
#define IN 0
#define OUT 1

int state = OUT;     // state of the cursor IN-inside comment OUT-outside comment
int getline(char line[], int limit);
int comment_start(char line[], int position);
int comment_end(char line[], int position);

int main(void)
{
  int len, i;
  char l[MAXLINE];

  while ((len = getline(l, MAXLINE)) > 0)   // while length of line > 0 read line
    {
      i = 0;                    // initialize counter
      while (l[i+1] != '\0')    // if next char is not NULL
	if (state == OUT)       // if outside comment
	  {
	    if (comment_start(l, i)) // if a comment starts
	      state = IN;            // change state to inside comment
	    else
	      putchar(l[i]);
	    ++i;                     // print char and increment 
	  }
	else
	  {
	    ++i;
	    if (comment_end(l, i))  // if comment ends
	      {
		state = OUT; 
		++i;                // change state to outside comment and increment
	      }
	  }
    }

  return 0;
}                                                                                       

int getline(char l[], int lim)
{
  int c, i;

  for (i = 0; (i < lim) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
    l[i] = c;
  if (c == '\n')
    {
      l[i] = c;
      ++i;
    }
  l[i] = '\0';
  return i;
}

/* comment_start: returns 1 if a comment starts, and 0 otherwise. */
int comment_start(char s[], int i)
{
  if ((s[i] == '/') && (s[i+1] == '*'))
    if (!(inside_quotes(s, i-1)))
      return 1;
  return 0;
}

/* comment_end: returns 1 if the comment ends, 0 otherwise. */
int comment_end(char s[], int i)
{
  if ((s[i] == '/') && s[i-1] == '*')
    return 1;
  else
    {
      return 0;
    }
}

/* inside_quotes: returns 1 if char is inside quotes, 0 otherwise*/
int inside_quotes(char s[], int n)
{
  int i, quotes = 0;

  for(i = 0; i <= n; ++i)
    if (s[i] == '"')
      if (s[i-1] != 27)   // if quote is not escaped
	++quotes;
  return (quotes % 2);     // if the number of quotes is odd => inside quotes 
}
