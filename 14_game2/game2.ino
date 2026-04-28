#include <LedControl.h>
#include <TM1637Display.h>

// LED Matrix (DIN, CLK, CS, number of devices)
LedControl lc = LedControl(12, 11, 10, 3);

// TM1637 (CLK, DIO)
TM1637Display display(2, 3);

// Buttons
#define BTN_SMILE 4
#define BTN_SAD   5

int score = 0;
int currentFace = 0; // 0 = smile, 1 = sad

unsigned long lastChange = 0;
int interval = 1000; // change every 1 sec

// 🙂 Smiley
byte smile[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

// ☹️ Sad
byte sad[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

void setup() {
  // Init matrices
  for (int i = 0; i < 3; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }

  // Buttons
  pinMode(BTN_SMILE, INPUT_PULLUP);
  pinMode(BTN_SAD, INPUT_PULLUP);

  // Display
  display.setBrightness(7);

  randomSeed(analogRead(0));

  // Static faces
  drawFace(0, smile); // Matrix 1
  drawFace(1, sad);   // Matrix 2
}

void loop() {
  // Change random face
  if (millis() - lastChange > interval) {
    lastChange = millis();
    currentFace = random(0, 2);

    if (currentFace == 0) {
      drawFace(2, smile);
    } else {
      drawFace(2, sad);
    }
  }

  // Button check
  if (digitalRead(BTN_SMILE) == LOW) {
    if (currentFace == 0) {
      score++;
      updateDisplay();
    }
    delay(200); // debounce
  }

  if (digitalRead(BTN_SAD) == LOW) {
    if (currentFace == 1) {
      score++;
      updateDisplay();
    }
    delay(200);
  }
}

// Draw face on matrix
void drawFace(int matrix, byte face[]) {
  for (int i = 0; i < 8; i++) {
    lc.setRow(matrix, i, face[i]);
  }
}

// Update TM1637 score
void updateDisplay() {
  display.showNumberDec(score);
}