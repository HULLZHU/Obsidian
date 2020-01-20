#ifndef _OBSLOGGER_H_
#define _OBSLOGGER_H_

int obsWritePath(char *path, char *buf);
int obsWriteFd(const int fd, const char *buf);
int obsLoggerWritePath( const char *path, const char *title, const char *fmt,...);
int obsLoggerWriteFd( const int fd , const char *title ,const char *fmt,...);

#endif