#include <LedControl.h>

LedControl lc = LedControl(12, 11, 10, 1);

// lowercase 'a'
byte a[8] = {
  B00000000,
  B00111100,
  B00000010,
  B00111110,
  B01000010,
  B01000010,
  B00111110,
  B00000000
};

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, a[i]);
  }
}

void loop() {}