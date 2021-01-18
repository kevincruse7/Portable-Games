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

#endif  // __AVR_ATmega2560__