#ifndef Jump_h
#define Jump_h

#include <Arduino.h>

// reconection
void jump() {
  delay(1000);
  ESP.restart();
}
#endif