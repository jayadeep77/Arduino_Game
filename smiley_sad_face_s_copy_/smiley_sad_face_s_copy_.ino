#include <LedControl.h>

LedControl lc = LedControl(12, 11, 10, 2);

byte A[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

byte B[8] = {
  B01111110,
  B10000001,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B10000001,
  B01111110
};

void setup() {
  for (int i = 0; i < 2; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 0);
    lc.clearDisplay(i);
  }

  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, A[i]); // FIRST LED → A
    lc.setRow(1, i, B[i]); // SECOND LED → B
  }
}

void loop() {}
