#include <TM1637Display.h>

// TM1637 pins
#define CLK 3
#define DIO 2

// Buttons
#define BTN_UP 4
#define BTN_DOWN 5

TM1637Display display(CLK, DIO);

int count = 0;

void setup() {
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);

  display.setBrightness(5);
  display.showNumberDec(count, true);
}

void loop() {

  // 🔼 Increase
  if (digitalRead(BTN_UP) == LOW) {
    count++;
    if (count > 9999) count = 9999;   // upper limit
    display.showNumberDec(count, true);
    delay(200); // debounce
  }

  // 🔽 Decrease
  if (digitalRead(BTN_DOWN) == LOW) {
    count--;
    if (count < -999) count = -999;   // lower limit
    display.showNumberDec(count, true);
    delay(200); // debounce
  }
}