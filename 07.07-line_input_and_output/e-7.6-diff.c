/* Write a program to compare two files, printing the first line where they differ. */
#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char *argv[])
{
  FILE *f1, *f2;
  char l1[MAXLINE], l2[MAXLINE];
  char *prog = argv[0];
  
  if (argc != 3)
    {
      printf("error: the program takes 2 arguments;\n");
      return 0;
    }
  else
    if ((f1 = fopen(*++argv, "r")) != NULL) 
      if ((f2 = fopen(*++argv, "r")) != NULL)
    	while (fgets(l1, MAXLINE, f1) != NULL && fgets(l2, MAXLINE, f2) != NULL)
	  {
	    if (strcmp(l1, l2) != 0)
	      {
		printf("%s", l1);
		printf("%s", l2);
		fclose(f1);
		fclose(f2);
		return 0;
	      }
	  }
      else
	{
	  fprintf(stderr, "%s can't open %s", prog, *argv);
	  exit(1);
	}
    else
      {
    	fprintf(stderr, "%s can't open %s", prog, *argv);
    	exit(1);
      }
  printf("Identical lines\n");
  return 0;
}
