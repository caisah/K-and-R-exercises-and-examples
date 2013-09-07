#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(void)
{
  int y = 1984, m = 6, d = 30, yd = 366;
  int *pm, *pd;

  printf("Day: %d\n", day_of_year(y, m, d));
  month_day(y, yd, pm, pd);
  printf("Month: %d, Day: %d\n", *pm, *pd);
  return 0;
}
static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* day_of_year: set day of year form month & day */
int day_of_year(int year, int month, int day)
{
  int i, leap;

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  if (month < 1 || month > 12)
    {
      printf("error: invalid month!\n");
      return -1;
    }
  if (day < 1 || day > daytab[leap][month])
    {
      printf("error: invalid day!\n");
      return -1;
    }
  for (i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  if (leap)
    {
      if (yearday > 365)
	{
	  printf("error: not a valid day!\n");
	  return;
	}
    }
  else
    if (yearday > 366)
      {
	printf("error: not a valid day!\n");
	return;	
      }
    
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
}
  
