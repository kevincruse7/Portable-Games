#ifndef SYSTEM_TIME_H
#define SYSTEM_TIME_H

typedef unsigned long SystemTime;

SystemTime getSystemTime(void);

void systemTimeSleep(SystemTime time);

#endif // SYSTEM_TIME_H
