#ifndef BuzzerPlayer_h
#define BuzzerPlayer_h

#include <Arduino.h>

#define BUZZER_PIN 15
#define BUZZER_RESOLUTION 8
#define BUZZER_FREQUENCY 2000

// Notes
#define NOTE_B3  247
#define NOTE_E4  330
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_E5  659
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988
#define NOTE_E6  1318

// Functions

void setupBuzzer() {
  // Initialize the buzzer pin with specified frequency and resolution
  if (!ledcAttach(BUZZER_PIN, BUZZER_FREQUENCY, BUZZER_RESOLUTION)) {
    Serial.println("Failed to attach buzzer pin to LEDC");
  }
}

void toneQuiet(int freq, int duration) {
  // Play tone at specified frequency
  ledcWriteTone(BUZZER_PIN, freq);
  delay(duration);
  // Stop tone
  ledcWriteTone(BUZZER_PIN, 0);
  delay(30);
}

void playExtendedZeldaFanfare() {
  toneQuiet(NOTE_B3, 120);
  toneQuiet(NOTE_E4, 120);
  toneQuiet(NOTE_G4, 120);
  toneQuiet(NOTE_A4, 120);
  toneQuiet(NOTE_B4, 180);

  delay(100);

  toneQuiet(NOTE_B4, 150);
  toneQuiet(NOTE_E5, 150);
  toneQuiet(NOTE_G5, 150);
  toneQuiet(NOTE_FS5, 150);
  toneQuiet(NOTE_A5, 150);
  toneQuiet(NOTE_B5, 300);

  delay(150);

  toneQuiet(NOTE_E5, 100);
  toneQuiet(NOTE_G5, 100);
  toneQuiet(NOTE_E6, 400);
}

void playRabbitJump() {
  // A quick ascending "boing" style sequence to simulate a jump
  toneQuiet(NOTE_E4, 50);
  toneQuiet(NOTE_G4, 50);
  toneQuiet(NOTE_B4, 60);
  toneQuiet(NOTE_E5, 70);
  toneQuiet(NOTE_E4, 50);
  toneQuiet(NOTE_G4, 50);
  toneQuiet(NOTE_B4, 60);
  toneQuiet(NOTE_E5, 70);
}


#endif
