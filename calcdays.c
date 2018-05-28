#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "calcdays.h"

/* get current sysem date */
struct tm GetCurrentDate()
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	return (tm);
}

/* local function to get find whether the given year is leap year or not */
void find_leap(int month, int ip_year)
{
	if (month == 2) {
		if ((ip_year % 4) == 0) {
			if ((ip_year % 100) == 0) {
				if ((ip_year % 400) == 0) {
					ar_days[1] = 29;
				}
				else {
					ar_days[1] = 28;
				}
			}
			else {
				ar_days[1] = 29;
			}		
		}
		else {
			ar_days[1] = 28;
		}
	}
}

/* accumulate completed days from starting month to current month in this current year */
int calc_cur_month(int cur_date, int cur_mon, int cur_year)
{
	int cal_cur_days = 0;
 	
	/* find whether the current year is leap year or not */
	find_leap(cur_mon, cur_year);

	if (cur_mon == 2) {
		cal_cur_mon = 1;
		cal_cur_days = ar_days[0] + cur_date;
	}
	else if (cur_mon == 3) {
		cal_cur_mon = 2;
		cal_cur_days = ar_days[0] + ar_days[1] + cur_date;
	}
	else if (cur_mon == 4) {
		cal_cur_mon = 3;
		cal_cur_days = ar_days[0] + ar_days[1] + ar_days[2] + cur_date;
	}
	else if (cur_mon == 5) {
		cal_cur_mon = 4;
		cal_cur_days = ar_days[0] + ar_days[1] + ar_days[2] + ar_days[3] + cur_date;
	}
	else if (cur_mon == 6) {
		cal_cur_mon = 5;
		cal_cur_days = ar_days[0] + ar_days[1] + ar_days[2] + ar_days[3] + ar_days[4] + cur_date;
	}
	else if (cur_mon == 7) {
		cal_cur_mon = 6;
		cal_cur_days = ar_days[0] + ar_days[1] + ar_days[2] + ar_days[3] + ar_days[4] + ar_days[5] + cur_date;
	}
	else if (cur_mon == 8) {
		cal_cur_mon = 7;
		cal_cur_days = ar_days[0] + ar_days[1] + ar_days[2] + ar_days[3] + ar_days[4] + ar_days[5] + ar_days[6] + cur_date;
	}
	else if (cur_mon == 9) {
		cal_cur_mon = 8;
		cal_cur_days = ar_days[0] + ar_days[1] + ar_days[2] + ar_days[3] + ar_days[4] + ar_days[5] + ar_days[6] + ar_days[7] + cur_date;
	}
	else if (cur_mon == 10) {
		cal_cur_mon = 9;
		cal_cur_days = ar_days[0] + ar_days[1] + ar_days[2] + ar_days[3] + ar_days[4] + ar_days[5] + ar_days[6] + ar_days[7] + ar_days[8] + cur_date;
	}
	else if (cur_mon == 11) {
		cal_cur_mon = 10;
		cal_cur_days = ar_days[0] + ar_days[1] + ar_days[2] + ar_days[3] + ar_days[4] + ar_days[5] + ar_days[6] + ar_days[7] + ar_days[8] + ar_days[9] + cur_date;
	}
	else if (cur_mon == 12) {
		cal_cur_mon = 11;
		cal_cur_days = ar_days[0] + ar_days[1] + ar_days[2] + ar_days[3] + ar_days[4] + ar_days[5] + ar_days[6] + ar_days[7] + ar_days[8] + ar_days[9] + ar_days[10] + cur_date;
	}
	return cal_cur_days;
}

/* accumulate remaining days from the given month to last month in given year */
void calc_month(int date, int month, int year, int cur_date, int cur_mon, int cur_year)
{
	int cal_cur_days = 0, cal_bal_days = 0, mon_diff = 0;

	if (cur_mon == 1) {
		cal_cur_mon = 0;
		cal_cur_days = cur_date;
	}
	else {
		/* calling to calculate completed days from current month in current year */
		cal_cur_days = calc_cur_month(cur_date, cur_mon, cur_year);

		/* set days only, if given month, year and current month, year are matches */
		if (cur_year == year) {
			
			if (month < cur_mon) {
				mon_diff = cur_mon - month;
				cal_days = (mon_diff * 30) + cur_date;
			}
			else if (month == cur_mon) {
				cal_days = (cur_date - date) + 1;	
			}			
			else {
				cal_days = cal_cur_days;
			}
		}
	}

	if (cur_year != year) {
		/* find whether the given year is leap year or not */
		find_leap(month, year);
		
		if (month == 1) {
			cal_birth_mon = MAX_MONTH - month;
			cal_bal_days = (ar_days[0] - date) + 1; 
			cal_days = ar_days[1] + ar_days[2] + ar_days[3] + ar_days[4] + ar_days[5] + ar_days[6] + ar_days[7] + ar_days[8] + ar_days[9] + ar_days[10] + ar_days[11];
			cal_days = cal_days + cal_cur_days + cal_bal_days;
		}
		else if (month == 2) {
			cal_birth_mon = MAX_MONTH - month;
			cal_bal_days = (ar_days[1] - date) + 1;
			cal_days = ar_days[2] + ar_days[3] + ar_days[4] + ar_days[5] + ar_days[6] + ar_days[7] + ar_days[8] + ar_days[9] + ar_days[10] + ar_days[11];
			cal_days = cal_days + cal_cur_days + cal_bal_days;
		}
		else if (month == 3) {
			cal_birth_mon = MAX_MONTH - month;
			cal_bal_days = (ar_days[2] - date) + 1;
			cal_days = ar_days[3] + ar_days[4] + ar_days[5] + ar_days[6] + ar_days[7] + ar_days[8] + ar_days[9] + ar_days[10] + ar_days[11];
			cal_days = cal_days + cal_cur_days + cal_bal_days;
		}
		else if (month == 4) {
			cal_birth_mon = MAX_MONTH - month;
			cal_bal_days = (ar_days[3] - date) + 1;
			cal_days = ar_days[4] + ar_days[5] + ar_days[6] + ar_days[7] + ar_days[8] + ar_days[9] + ar_days[10] + ar_days[11];
			cal_days = cal_days + cal_cur_days + cal_bal_days;
		}
		else if (month == 5) {
			cal_birth_mon = MAX_MONTH - month;
			cal_bal_days = (ar_days[4] - date) + 1;
			cal_days = ar_days[5] + ar_days[6] + ar_days[7] + ar_days[8] + ar_days[9] + ar_days[10] + ar_days[11];
			cal_days = cal_days + cal_cur_days + cal_bal_days;
		}
		else if (month == 6) {
			cal_birth_mon = MAX_MONTH - month;
			cal_bal_days = (ar_days[5] - date) + 1;
			cal_days = ar_days[6] + ar_days[7] + ar_days[8] + ar_days[9] + ar_days[10] + ar_days[11];
			cal_days = cal_days + cal_cur_days + cal_bal_days;
		}
		else if (month == 7) {
			cal_birth_mon = MAX_MONTH - month;
			cal_bal_days = (ar_days[6] - date) + 1;
			cal_days = ar_days[7] + ar_days[8] + ar_days[9] + ar_days[10] + ar_days[11];
			cal_days = cal_days + cal_cur_days + cal_bal_days;
		}
		else if (month == 8) {
			cal_birth_mon = MAX_MONTH - month;
			cal_bal_days = (ar_days[7] - date) + 1;
			cal_days = ar_days[8] + ar_days[9] + ar_days[10] + ar_days[11];
			cal_days = cal_days + cal_cur_days + cal_bal_days;
		}
		else if (month == 9) {
			cal_birth_mon = MAX_MONTH - month;
			cal_bal_days = (ar_days[8] - date) + 1;
			cal_days = ar_days[9] + ar_days[10] + ar_days[11];
			cal_days = cal_days + cal_cur_days + cal_bal_days;
		}	
		else if (month == 10) {
			cal_birth_mon = MAX_MONTH - month;
			cal_bal_days = (ar_days[9] - date) + 1;
			cal_days = ar_days[10] + ar_days[11];
			cal_days = cal_days + cal_cur_days + cal_bal_days;
		}
		else if (month == 11) {
			cal_birth_mon = MAX_MONTH - month;
			cal_bal_days = (ar_days[10] - date) + 1;
			cal_days = ar_days[11];
			cal_days = cal_days + cal_cur_days + cal_bal_days;
		}
	}
	/* accumulate remaining days in given month and completed days in current month */
	cal_birth_day = cal_bal_days + cur_date;
}

/* display number of days with completed years, months, and days */
void display(int date, int month, int year, int cur_date, int cur_month, int cur_year, int tot_days, 
		int ip_yr, int ip_mon, int ip_day)
{
	printf("\n----------------------------------------------------------------------------------------\n");
	printf("\n\t\t\t DAYS CALCULATOR \t\t\t\n");
	printf("\n----------------------------------------------------------------------------------------\n");
	printf(" Given-Date: %d\t\t Given-Month: %d\t\t Given-Year: %d\t\t\n", date, month, year);
	printf(" System-Date: %d\t System-Month: %d\t System-Year: %d\t\n", cur_date, cur_month, cur_year);
	printf("\n Number of Days: %d(Days) -----> %d(years)\t %d(months)\t %d(days)\t\n", tot_days, ip_yr, ip_mon, ip_day); 
	printf("----------------------------------------------------------------------------------------\n");
	printf("\n These above days are calculated based on the current system date\n");
	printf("****************************************************************************************\n");
}

int main()
{
	int date, month, year, cur_date, cur_month, cur_year, tot_days = 0, ip_yr = 0, ip_mon = 0;
	int cal_bal_day, loop_cnt = 0, leap_yr = 0, leap_yr_cnt = 0, diff_mon = 0;
	char dob[10];
	char *split_date, *split_month, *split_year;
	char delim[] = "/";
	struct tm curdate;
	
	/* from this date to current date to find number of days */
	printf("Enter your date of birth (DD/MM/YYYY)\n");
	scanf("%s", dob);
	
	/* split date alone from the given date */
	split_date = strtok(dob, delim);
	date = atoi(split_date);
	
	/* restrictions in entering date, otherwise throw error */
	if ((date < 1) || (date > 31)) {
		ERR_LOG(("Error: Invalid date, please enter valid date should not exceed 31\n"));
		return(0);
	}
		
	/* split month alone from the given month */
	split_month = strtok(NULL, delim);
	month = atoi(split_month);

	/* restrictions in entering month, otherwise throw error */
	if ((month < 1) || (month > 12)) {
		ERR_LOG(("Error: Invalid month, please enter month should not exceed 12\n"));
		return(0);
	}
	
	/* restrictions in entering date in Febraury, otherwise throw error */
	if ((month == 2) && (date >= 28)) {
		ERR_LOG(("Error: Invalid date, Febraury month have maximum 29 days in leap year and 28 days in others\n"));
		return (0);
	}
	
	/* split year alone from the given year */
	split_year = strtok(NULL, delim);
	year = atoi(split_year);

	/* get current system date */
	curdate = GetCurrentDate();
	
	cur_date = curdate.tm_mday;
	cur_month = curdate.tm_mon + 1;
	cur_year = curdate.tm_year + 1900;
	
	PRINT(("\n----------------------------------------------------------------------------------------\n"));
	PRINT(("Current Day : %d\n", cur_date));
	PRINT(("Current Month : %d\n", cur_month));
	PRINT(("Current Year : %d\n", cur_year));
	
	/* restrictions in entering year, otherwise throw error */
	if (year > cur_year || year <= 1900) {
		ERR_LOG(("Error: Invalid year, please enter year starts from 1900 to current year\n"));
		return(0);
	}
	
	/* restrictions in entering month in same year, otherwise throw error */
	if (cur_year == year) {
		if (month > cur_month) {
			ERR_LOG(("Error: Invalid month, Please enter less than current month\n"));
			return(0);
		}		
	}
	
	/* accumulate total days from current system year to given year */
	if (cur_year != year) {
		ip_yr = ((cur_year - 1) - year);
		tot_days = ip_yr * 365;
	}
	
	leap_yr = year + 1;

	/* accumulate extra one day in each leap year in between the given year and current year */	
	PRINT(("Leap year occurs in between given year and current year: "));
	for (loop_cnt = leap_yr; loop_cnt < cur_year; loop_cnt++) {
		if (((loop_cnt % 4 == 0) && (loop_cnt % 100 != 0)) || (loop_cnt % 400 == 0)) {
			leap_yr_cnt++;
			PRINT((" %d", loop_cnt));
		}
	}
	PRINT(("\n-------------------------------------------------------------------------------------------"));
	
	/* accumulate days for last month from given month in given year */
	if (month == MAX_MONTH) {
		cal_birth_mon = MAX_MONTH - month;
		cal_bal_day = ar_days[11] - date;
		tot_days = tot_days + leap_yr_cnt + cal_bal_day;

		if (year == cur_year) {
			if (month == cur_month) {
				ip_mon = 0; 
			}
			else {
				diff_mon = cur_month - month;
				ip_mon = diff_mon;
			}
		}
		else {
			ip_mon = cal_birth_mon + cal_cur_mon;
		}
	}
	else {	
		calc_month(date, month, year, cur_date, cur_month, cur_year);
		
		if (year == cur_year) {
			if (month == cur_month) {
				ip_mon = 0;
			}
			else {
				diff_mon = cur_month - month;
				ip_mon = diff_mon;				
			}
		}
		else {
			ip_mon = cal_birth_mon + cal_cur_mon;
		}
		tot_days = tot_days + leap_yr_cnt + cal_days;
	}

	if (cal_birth_day >= MAX_DAY) {
		ip_mon = ip_mon + 1;
		cal_birth_day = cal_birth_day - MAX_DAY;

		if (ip_mon >= MAX_MONTH) {
			ip_yr = ip_yr + 1;
			ip_mon = ip_mon - MAX_MONTH;
		}
	}
	display(date, month, year, cur_date, cur_month, cur_year, tot_days, ip_yr, ip_mon, cal_birth_day);
}
