/**
 * Module defines a standardized, platform-independent method of retrieving the current system time and sleeping.
 *
 * @author Kevin Cruse
 */
#ifndef SYSTEM_TIME_H
#define SYSTEM_TIME_H


/**
 * Defines a type for system time in milliseconds.
 */
typedef unsigned long SystemTime;


/**
 * Retrieves the current system time.
 *
 * @returns Current system time.
 */
SystemTime system_time_get(void);


/**
 * Sleeps for the given duration of time.
 *
 * @param time Time to sleep for.
 */
void system_time_sleep(SystemTime time);


#endif
