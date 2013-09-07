/* Write a program to print a set of files, starting each new one on a new page,
   with a title and a running page count for each file. */
#include <stdio.h>

#define MAXLINE 1000
#define PAGEROWS 50

int main(int argc, char *argv[])
{
  FILE *f;
  int pages = 0, rows, i;
  char line[MAXLINE];
  int count_pages(FILE *f);

  
  if (argc == 1)
    {
      printf("Not enough arguments!\n");
      return 0;
    }
  else
    while (--argc > 0)
      if ((f = fopen(*++argv, "r")) != NULL)
	{
	  pages = count_pages(f);
	  printf("File: %s, %d pages\n", *argv, pages);
	  rows = 0;
	  if ((fgets(line, MAXLINE, f)) == NULL)
	    printf("NULL");
	  while ((fgets(line, MAXLINE, f)) != NULL)
	    {
	      rows++;
	      printf("%s", line);
	    }
	  for (i = rows % PAGEROWS; i <= PAGEROWS; i++ )
	    printf("\n");
	  fclose(f);
	}
      else
	{
	  fprintf(stderr, "can't opne %s", *argv);
	  exit(1);
	}
  return 0;
}

int count_pages(FILE *f)
{
  int rows = 0;
  char line[MAXLINE];
  
  while ((fgets(line, MAXLINE, f)) != NULL)
    rows++;
  rewind(f);
  return rows / PAGEROWS + 1;
}
