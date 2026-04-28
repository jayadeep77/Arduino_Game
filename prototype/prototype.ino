#include <LedControl.h>
#include <TM1637Display.h>

LedControl lc = LedControl(12, 11, 10, 3);
TM1637Display display(2, 3);

#define BTN_SMILE 4
#define BTN_SAD   5

int score = 0;
int currentFace = 0;
bool waitingForInput = true;

unsigned long gameStartTime;
bool gameRunning = false;

// 🙂 Smiley
byte smile[8] = {
  B00111100,B01000010,B10100101,B10000001,
  B10100101,B10011001,B01000010,B00111100
};

// ☹️ Sad
byte sad[8] = {
  B00111100,B01000010,B10100101,B10000001,
  B10011001,B10100101,B01000010,B00111100
};

// S
byte S_char[8] = {
  B00111100,B01000010,B01000000,B00111100,
  B00000010,B01000010,B00111100,B00000000
};

// E
byte E_char[8] = {
  B01111110,B01000000,B01000000,B01111100,
  B01000000,B01000000,B01111110,B00000000
};

void setup() {
  for (int i = 0; i < 3; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }

  pinMode(BTN_SMILE, INPUT_PULLUP);
  pinMode(BTN_SAD, INPUT_PULLUP);

  display.setBrightness(7);
  randomSeed(analogRead(0));

  // Show "S" at start
  drawAll(S_char);
  delay(2000);

  // Start game
  gameRunning = true;
  gameStartTime = millis();

  // Static faces
  drawFace(0, smile);
  drawFace(1, sad);

  generateNewFace();
}

void loop() {

  if (!gameRunning) return;

  // Check time limit (30 sec)
  if (millis() - gameStartTime >= 30000) {
    gameRunning = false;
    drawAll(E_char);
    return;
  }

  // Wait for correct input
  if (waitingForInput) {

    if (digitalRead(BTN_SMILE) == LOW) {
      checkAnswer(0);
      delay(200);
    }

    if (digitalRead(BTN_SAD) == LOW) {
      checkAnswer(1);
      delay(200);
    }
  }
}

// Generate one random face
void generateNewFace() {
  currentFace = random(0, 2);
  if (currentFace == 0) drawFace(2, smile);
  else drawFace(2, sad);

  waitingForInput = true;
}

// Check answer
void checkAnswer(int pressed) {
  if (pressed == currentFace) {
    score++;
    display.showNumberDec(score);
    generateNewFace(); // ONLY change after correct
  }
  // wrong → do nothing
}

// Draw on one matrix
void drawFace(int matrix, byte face[]) {
  for (int i = 0; i < 8; i++) {
    lc.setRow(matrix, i, face[i]);
  }
}

// Draw same on all
void drawAll(byte face[]) {
  for (int m = 0; m < 3; m++) {
    for (int i = 0; i < 8; i++) {
      lc.setRow(m, i, face[i]);
    }
  }
}