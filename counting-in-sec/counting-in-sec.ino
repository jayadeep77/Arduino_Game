#include <TM1637Display.h>

#define CLK 3
#define DIO 2

#define BTN_INC 4
#define BTN_DEC 5

TM1637Display display(CLK, DIO);

int value = 0;

void setup() {
  display.setBrightness(5);

  pinMode(BTN_INC, INPUT_PULLUP);
  pinMode(BTN_DEC, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(BTN_INC) == LOW) {
    value++;
    if (value > 9999) value = 9999;
    delay(200);  // basic debounce
  }

  if (digitalRead(BTN_DEC) == LOW) {
    value--;
    if (value < 0) value = 0;
    delay(200);  // basic debounce
  }

  display.showNumberDec(value);
}