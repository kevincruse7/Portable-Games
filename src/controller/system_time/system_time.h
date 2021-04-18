/*
 * Copyright 2021 Kevin Matthew Cruse
 * This file is part of Portable Games.
 *
 * Portable Games is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Portable Games is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Portable Games. If not, see <https://www.gnu.org/licenses/>.
 */


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
