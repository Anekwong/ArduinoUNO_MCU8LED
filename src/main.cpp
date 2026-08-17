#include <Arduino.h>

const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int ledCount = 8;
bool ledStates[] = {false, false, false, false, false, false, false, false};

void toggleLed(int index);
void allOn();
void allOff();
void runTwoLedsLeftToRight();
void runOneLedRightToLeft();

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  Serial.println("Arduino UNO R3 LED Control Ready");
  Serial.println("Press A-H to toggle LED1-LED8");
  Serial.println("Press I = all ON, J = all OFF");
  Serial.println("Press K = 2 LEDs run left to right");
  Serial.println("Press L = 1 LED run right to left");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command >= 'a' && command <= 'z') {
      command = command - 32;
    }

    switch (command) {
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
        toggleLed(command - 'A');
        break;

      case 'I':
        allOn();
        break;

      case 'J':
        allOff();
        break;

      case 'K':
        runTwoLedsLeftToRight();
        break;

      case 'L':
        runOneLedRightToLeft();
        break;
    }
  }
}

void toggleLed(int index) {
  ledStates[index] = !ledStates[index];
  digitalWrite(ledPins[index], ledStates[index] ? HIGH : LOW);
}

void allOn() {
  for (int i = 0; i < ledCount; i++) {
    ledStates[i] = true;
    digitalWrite(ledPins[i], HIGH);
  }
}

void allOff() {
  for (int i = 0; i < ledCount; i++) {
    ledStates[i] = false;
    digitalWrite(ledPins[i], LOW);
  }
}

void runTwoLedsLeftToRight() {
  allOff();

  for (int i = 0; i < ledCount - 1; i++) {
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[i + 1], HIGH);
    delay(300);
    digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[i + 1], LOW);
  }
}

void runOneLedRightToLeft() {
  allOff();

  for (int i = ledCount - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(300);
    digitalWrite(ledPins[i], LOW);
  }
}
