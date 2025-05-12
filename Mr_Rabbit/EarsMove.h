#ifndef EarsMove_h
#define EarsMove_h

#include <ESP32Servo.h>
//#include "BuzzerPlayer.h" 

Servo servo1;
Servo servo2;
 
#define SERVO1_PIN 16
#define SERVO2_PIN 17

//#define SERVO1_ROTATE_FORWARD  95
//#define SERVO2_ROTATE_FORWARD  102
//#define SERVO1_ROTATE_BACK     81
//#define SERVO2_ROTATE_BACK     80

//#define SERVO1_ROTATE_FORWARD  105   // more forward tilt
//#define SERVO2_ROTATE_FORWARD  107
//#define SERVO1_ROTATE_BACK     72    // more backward tilt
//#define SERVO2_ROTATE_BACK     73

#define SERVO1_ROTATE_FORWARD  90
#define SERVO2_ROTATE_FORWARD  94
#define SERVO1_ROTATE_BACK     90
#define SERVO2_ROTATE_BACK     88

#define ROTATE_STOP            88

void setupEars() {
  servo1.attach(SERVO1_PIN, 200, 2800);
  servo2.attach(SERVO2_PIN, 800, 2200);
  
  //setupBuzzer();
}

void moveEars() {
  // Start
  for (int i = 0; i < 5; i++) {
    // servo1.write(SERVO1_ROTATE_BACK);
    // servo2.write(SERVO2_ROTATE_FORWARD);
    // delay(100);
    // servo1.write(SERVO1_ROTATE_FORWARD);
    // servo2.write(SERVO2_ROTATE_BACK);
    // delay(200);
    // servo1.write(SERVO1_ROTATE_BACK);
    // servo2.write(SERVO2_ROTATE_FORWARD);
    // delay(100);
    // servo1.write(ROTATE_STOP);
    // servo2.write(ROTATE_STOP);
    // delay(10);
    servo1.write(SERVO1_ROTATE_BACK);
    servo2.write(SERVO2_ROTATE_BACK);
    delay(100);
    servo1.write(SERVO1_ROTATE_FORWARD);
    servo2.write(SERVO2_ROTATE_FORWARD);
    delay(200);
    servo1.write(SERVO1_ROTATE_BACK);
    servo2.write(SERVO2_ROTATE_BACK);
    delay(100);
    servo1.write(ROTATE_STOP);
    servo2.write(ROTATE_STOP);
    delay(10);
  }

  // Stop
  servo1.write(ROTATE_STOP);
  servo2.write(ROTATE_STOP);

  //delay(500);
  //playExtendedZeldaFanfare();
}

#endif