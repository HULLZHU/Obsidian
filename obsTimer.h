#ifndef _DATE_MANAGER
#define _DATE_MANAGER

#define MMDDYY 1
#define YYMMDD 2
#define DDMMYY 3

#define INITYR 1900
#define INITMT 1

#define TMFORMAT12 0
#define TMFORMAT24 1

char *obsGetDate(const int format, const char *sep);

char *obsGetTime(const int format, const char *sep);

#endif