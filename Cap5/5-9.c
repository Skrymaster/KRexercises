#include <stdio.h>

static char daytab[2][13] =  {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year_pointer(int, int, int);
void month_day_pointer(int, int, int *, int *);

int main(void){
	int year, month, day, yearday;
	
	year = 2020;
	month = 3;
	day = 30;
	printf("Date: %d-%02d-%d\n", year, month, day);
	printf("day_of_year_pointer: %d\n", day_of_year_pointer(year, month, day));
	yearday = 90;
	month_day_pointer(year, yearday, &month, &day);
	printf("month_day_pointer: %d %d\n", month, day);
	
	return 0;
}

int day_of_year_pointer(int year, int month, int day){
	int i, leap;
	char *p;
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	p = &daytab[leap][1];
	for (i = 1; i < month; i++) {
		day += *p;
		++p;
	}
	return day;
}

void month_day_pointer(int year, int yearday, int *pmonth, int *pday){
	int i, leap;
	char *p;
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	p = &daytab[leap][1];
	for (i = 1; yearday > *p; i++) {
		yearday -= *p;
		++p;
	}
	*pmonth = i;
	*pday = yearday;
}

