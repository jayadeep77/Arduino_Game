#include <LedControl.h>

// DIN, CLK, CS
LedControl lc = LedControl(12, 11, 10, 1);

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

void setup() {
  lc.shutdown(0, false);   // Wake up display
  lc.setIntensity(0, 8);   // Brightness (0-15)
  lc.clearDisplay(0);

  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, A[i]);
  }
}

void loop() {
}