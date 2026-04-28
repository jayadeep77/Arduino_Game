#include <LedControl.h>

LedControl lc = LedControl(12, 11, 10, 2);

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

byte B[8] = {
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
  for (int i = 0; i < 2; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }

  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, A[i]); // FIRST LED → A
    lc.setRow(1, i, B[i]); // SECOND LED → B
  }
}

void loop() {}