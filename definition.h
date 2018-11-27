#ifndef DEFINITION_H
#define DEFINITION_H
#include <time.h>

#define LONG_STR_LEN 1024
#define MONTHS_PER_YEAR 12
#define HOURS_PER_DAY 24
#define MINUTES_PER_HOUR 60
#define DAYS_PER_WEEK 7

#define MONTH_MIN 1
#define MONTH_MAX 12
#define DAY_MIN 1
#define HOUR_MIN 0
#define HOUR_MAX 23
#define MINUTE_MIN 0
#define MINUTE_MAX 59
#define MAX_ROOM_CNT 1024
#define MAX_BORROW_CNT 65536

#define UNLIMITED 1000000000

typedef char Str16[16];
typedef char Str32[32];
typedef char Str64[64];
typedef char Str128[128];
typedef char String[LONG_STR_LEN];

typedef time_t Timestamp;

typedef int Week;

char *aWeekToString[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
int aDaysOfMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int aSumOfDaysBeforeMonth[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
const char *szPathToBaseInfo = "C:\\code\\myys\\classroom\\baseinfo.txt";
const char *szPathToCalssroomInfo = "C:\\code\\myys\\classroom\\info.txt";

#endif
