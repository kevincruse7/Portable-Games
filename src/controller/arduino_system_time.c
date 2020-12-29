#ifdef __AVR_ATmega2560__

#include "controller/system_time.h"

#include "Arduino.h"

SystemTime getSystemTime(void) {

  return millis();
}

void systemTimeSleep(SystemTime time) {

  delay(time);
}

#endif