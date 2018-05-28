#include <stdio.h>
#include <time.h>

#if 1 
	#define PRINT(X) printf X
#else 
	#define PRINT(X) (void)0
#endif

#define MAX_MONTH 12
#define MAX_DAY 30
#define ERR_LOG(E) printf E

/* Function prototypes */
struct tm GetCurrentDate();
void find_leap(int month, int ip_year);
void calc_month(int date, int month, int year, int cur_date, int cur_month, int cur_year);
int calc_cur_month(int cur_date, int cur_mon, int cur_year);
void display(int date, int month, int year, int cur_date, int cur_month, int cur_year, int tot_days, int ip_yr, int ip_mon, int ip_day);

/* Global declarations */
int cal_days;
int cal_year;
int cal_cur_mon;
int cal_birth_mon;
int cal_birth_day;
int ar_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

