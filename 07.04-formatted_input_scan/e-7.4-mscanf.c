/* Write a private version of scanf analogous to miniprintf from the previous section. */
#include <stdio.h>
#include <stdarg.h>

/* keep_reading: reads until new line or EOF*/
void keep_reading(void)
{
  char c;
  
  while ((c = getchar()) != '\n' || c != EOF)
    ;
}

/* miniprintf: minimal printf with variable argument list */
int mscanf(char *fmt, ...)
{
  va_list ap;  // points to each unnamed arg in turn
  char *p, *sval, c;
  int ival, count = 0;
  double dval;

  va_start(ap, fmt); // make ap point ot 1st unnamed arg
  for (p = fmt; *p; p++)
    {
      if (*p != '%')
	{
	  c = getchar();
	  if (c != *p)
	    {
	      keep_reading();
	      return 0;
	    }
	  else
	    continue;
	}
      switch (*++p)
	{
	case 'd':
	  ival = va_arg(ap, int);
	  count += scanf("%d", &ival);
	  break;
	case 'f':
	  dval = va_arg(ap, double);
	  count += scanf("%lf", &dval);
	  break;
	case 's':
	  sval = va_arg(ap, char *);
	  count += scanf("%s", sval);
	  break;
	default:
	  printf("wrong format!");
	  return 0;
	}
    }
  va_end(ap);    // clean up when done
  return count;
}

int main(void)
{
  int a;
  
  scanf("-%d", &a);
  printf("%d\n", a);
}
