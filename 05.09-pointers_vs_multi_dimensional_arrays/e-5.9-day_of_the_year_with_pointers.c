/* Rewrite the routines day_of_year and month_day with pointers 
   instead of indexing. */
#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int main(void)
{
  int y = 1984, m = 7, d = 12, yd = 194;
  int *pm, *pd;

  pm = &m;
  pd = &d;
  printf("Day: %d\n", day_of_year(y, m, d));
  month_day(y, yd, pm, pd);
  printf("Month: %d, Day: %d\n", *pm, *pd);
  return 0;
}

/* day_of_year: set day of year form month & day */
int day_of_year(int year, int month, int day)
{
  int i, leap;
  char *p;
  
  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  p = daytab[leap];
  for (i = 1; i < month; i++)
    day += *(p+i);
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;
  char *p;
	
  leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
  p = daytab[leap];
  for (i = 0; yearday > *p; i++, p++)
    yearday -= *p;
  *pmonth = i;
  *pday = yearday;
}
  
