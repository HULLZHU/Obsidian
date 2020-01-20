#include "obsTimer.h"
#include <stdio.h>
#include <time.h>


char *obsGetDate(const int format, const char *sep)
{   
    static char buf[32];

    time_t today = time(NULL);
    struct tm _tm = *localtime(&today);

    int year =  _tm.tm_year + INITYR;
    int month = _tm.tm_mon + INITMT;
    int day = _tm.tm_mday;
    

    switch(format)
    {
        case MMDDYY:
            sprintf(buf, "%02d%s%02d%s%04d", month, sep, day, sep, year);
            break;
        case YYMMDD:
            sprintf(buf, "%04d%s%02d%s%02d", year, sep, month, sep, day);
            break;
        case DDMMYY:
            sprintf(buf, "%02d%s%02d%s%04d", day, sep, month, sep, year);
            break;
        default:
            sprintf(buf, "%02d%s%02d%s%04d", month, sep, day, sep,year);
            break;
    }
    
    return buf;
}

char *obsGetTime(const int format,const char *sep)
{
    static char buf[32];

    time_t today = time(NULL);
    struct tm _tm = *localtime(&today);

    int hour =  _tm.tm_hour;
    int minute = _tm.tm_min;
    int seconds = _tm.tm_sec;
    

    switch(format)
    {
        case TMFORMAT12:
            sprintf(buf, "%02d%s%02d%s%02d-%s", hour > 12 ? (hour - 12) % 12:hour, sep, minute, sep, seconds, hour < 12 ? "AM" : "PM");
            break;
        case TMFORMAT24:
            sprintf(buf, "%02d%s%02d%s%02d", hour, sep, minute, sep, seconds);
            break;
        default:
            sprintf(buf, "%02d%s%02d%s%04d", hour, sep, minute, sep, seconds);
            break;
    }
    return buf;
}