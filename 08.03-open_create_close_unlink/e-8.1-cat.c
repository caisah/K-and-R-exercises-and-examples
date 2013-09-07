/* Rewrite the program cat from Chapter 7 using read, write, open and close instead of
   their standard library equivalents. Perform experiments to determine the relative speed
   of the two versions. */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void error(char *, ...);

int main(int argc, char *argv[])
{
  int f;
  void filecopy(int f1, int f2);

  if (argc == 1)
    filecopy(0, 1);
  else
    while (--argc > 0)
      if ((f = open(*++argv, O_RDONLY)) == -1)
	{
	  error("can't open %s", *argv);
	  return 1;
	}
      else
	{
	  filecopy(f, 1);
	  close(f);
	}
  return 0;
}

#include <stdarg.h>
/* error print an error message and die */
void error(char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  fprintf(stderr, "error: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

void filecopy(int from, int to)
{
  int n;
  char buf[BUFSIZ];

  while((n = read(from, buf, BUFSIZ)) > 0)
    write(to, buf, n);
}
