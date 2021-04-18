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
 * Implementation of the system time module for the Arduino Mega 2560.
 *
 * @author Kevin Cruse
 */
#ifdef __AVR_ATmega2560__
#include "system_time.h"


#include <Arduino.h>


SystemTime system_time_get(void) {
    return millis();
}


void system_time_sleep(SystemTime time) {
    delay(time);
}


#endif
