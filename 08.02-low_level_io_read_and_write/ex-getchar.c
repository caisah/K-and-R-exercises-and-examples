#include <stdio.h>
#include <unistd.h>

int getchar2(void);

int main(void)
{
  printf("%c\n", getchar2());
  return 0;
}


/* getchar2: simple buffered version of getchar*/
int getchar2(void)
{
  static char buf[BUFSIZ];
  static char *bufp = buf;
  static int n = 0;

  if (n == 0)   // buffer is empty
    {
      n = read(0, buf, sizeof buf);
      bufp = buf;
    }
  return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}
