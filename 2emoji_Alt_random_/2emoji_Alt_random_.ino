#include <TM1637Display.h>

#define CLK 3
#define DIO 2

TM1637Display display(CLK, DIO);

int seconds = 0;

void setup() {
  display.setBrightness(5);  
}

void loop() {
  display.showNumberDec(seconds);

  delay(1000);   
  seconds++;

  if (seconds > 10) {
    seconds = 0; 
  }
}