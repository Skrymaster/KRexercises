#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };

int day_of_year(int, int, int);
int month_day(int, int, int *, int *);

int main(void){
	int year, month, day, yearday;
    // dacă dau year -1 dă erori pentru că am setat ca anul să nu fie negativ
	for (year = 0; year <= 2020; ++year) {
		for (yearday = 1; yearday < 366; ++yearday) {
			if (month_day(year, yearday, &month, &day) == -1) {
				printf("error month_day at:year %d and yearday %d\n",year, yearday);
			} else if (day_of_year(year, month, day) != yearday) {
				printf("error year: %d, yearday: %d\n", year, yearday);
				printf("month: %d, day = %d\n", month, day);
			}
		}
	}
	return 0;
}

// totuşi aici nu prea văd rostul pentru error checking, nu prea are cum să dea erori decât dacă intenţionat introduceam date greşite
int day_of_year(int year, int month, int day){
	int i, leap;
	if (year < 0 || month < 1 || month > 12 || day < 1)
		return -1;

	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	if (day > daytab[leap][month])
		return -1;

	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday){
	int i, leap;
	if (year < 0 || yearday < 1)
		return -1;

	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	if ((leap && yearday > 366) || (!leap && yearday > 365))
		return -1;

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
	return 0;
}
