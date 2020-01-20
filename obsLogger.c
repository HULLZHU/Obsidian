#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <pthread.h>

#include "obsTimer.h"

/*@Write buf to a file, create if not exists*/
int obsWritePath(char *path, char *buf)
{
        int fd;
        fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0777);

        if (write(fd, buf, strlen(buf)) != (int)strlen(buf))
        {
                fprintf(stderr, "obsWritePath()--write()-line %d\n", __LINE__);
                close(fd);
                return -1;
        }
        else
        {
                close(fd);
        }

        return 0;
}

/*@Write buf to the fd*/
int obsWriteFd(const int fd, const char *buf)
{
        if (write(fd, buf, strlen(buf)) != (int)strlen(buf))
        {
                fprintf(stderr, "obsWriteFd()-write()-line %d\n", __LINE__);
                close(fd);
                return -1;
        }
        else
        {
                //write(fd, "\n", 1);
                close(fd);
        }

        return 0;
}

/*@Log to the file*/
int obsLoggerWritePath( const char *path, const char *title, const char *fmt,...)
{
        int fd;
        char buf[8192] = {0};

        fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0777);
        if(fd < 0 )
        {
                fprintf(stderr, "obsLoggerWritePath()-open()-line %d\n", __LINE__);
                close(fd);
                return -1;
        }

        char mesg[4096] = {0};
        va_list ap;
        va_start(ap, fmt);
        vsprintf(mesg, fmt, ap);
        va_end(ap);

        int len = snprintf(buf, sizeof(buf),"%s", title);
        if(len < 0 )
        {
                fprintf(stderr, "bsLoggerWritePath()-snprintf()-line %d\n", __LINE__);
                close(fd);
                return -1;
        }
        len = snprintf(buf + len, sizeof(buf) - len, "%s ---%s %s\n", mesg, obsGetDate(YYMMDD,"/"), obsGetTime(TMFORMAT24,":"));

        if(len < 0 )
        {
                fprintf(stderr, "bsLoggerWritePath()-snprintf()-line %d\n", __LINE__);
                close(fd);
                return -1;
        }

        obsWriteFd(fd, buf);

        return 0;
}


/*@Log to the fd*/
int obsLoggerWriteFd( const int fd , const char *title ,const char *fmt,...)
{
        char buf[8192] = {0};
        
        char mesg[4096] = {0};
        va_list ap;
        va_start(ap, fmt);
        vsprintf(mesg, fmt, ap);
        va_end(ap);

        int len = snprintf(buf, sizeof(buf),"%s", title);
        if(len < 0 )
        {
                fprintf(stderr, "bsLoggerWritePath()-snprintf()-line %d\n", __LINE__);
                close(fd);
                return -1;
        }
        len = snprintf(buf + len, sizeof(buf) - len, "%s ---%s %s\n", mesg, obsGetDate(YYMMDD,"/"), obsGetTime(TMFORMAT24,":"));

        if(len < 0 )
        {
                fprintf(stderr, "bsLoggerWritePath()-snprintf()-line %d\n", __LINE__);
                close(fd);
                return -1;
        }
        obsWriteFd(fd, buf);

        return 0;
}