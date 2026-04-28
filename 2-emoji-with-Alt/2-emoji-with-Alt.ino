#include <LedControl.h>

// DIN, CLK, CS, number of devices
LedControl lc = LedControl(12, 11, 10, 3);

// A pattern
byte A[8] = {
  B00111100,
  B01000010,
  B01000010,
  B01111110,
  B01000010,
  B01000010,
  B01000010,
  B00000000
};

// B pattern
byte B_char[8] = {
  B01111100,
  B01000010,
  B01000010,
  B01111100,
  B01000010,
  B01000010,
  B01111100,
  B00000000
};

void setup() {
  for (int i = 0; i < 3; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }

  randomSeed(analogRead(0)); // important for randomness

  displayChar(0, A);        // 1st = A
  displayChar(1, B_char);   // 2nd = B
}

void loop() {
  int choice = random(0, 2);          // 0 or 1
  int randomDelay = random(200, 1500); // random speed

  if (choice == 0) {
    displayChar(2, A);
  } else {
    displayChar(2, B_char);
  }

  delay(randomDelay);
}

void displayChar(int device, byte character[]) {
  for (int i = 0; i < 8; i++) {
    lc.setRow(device, i, character[i]);
  }
}