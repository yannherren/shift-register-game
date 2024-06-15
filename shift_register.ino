int DATA_PIN = 10;
int LATCH_PIN = 9;
int CLOCK_PIN = 8;
int BUTTON_PIN = 11;
int BUTTON_LED_NUMBER = 5;

int initialDelay = 300;
int level = 1;

int ledAnimationSequence[] = {
  0b10000000,
  0b01000000,
  0b00100000,
  0b00010000,
  0b00001000,
  0b00000100,
  0b00000010,
  0b00000001,
  0b00000010,
  0b00000100,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
};

int ledAnimationLength = sizeof(ledAnimationSequence) / sizeof(ledAnimationSequence[0]);

int startAnimationSequence[] = {
  0b11100000,
  0b11000000,
  0b10000000,
};

int startAnimationLength = sizeof(startAnimationSequence) / sizeof(startAnimationSequence[0]);

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  int currentDelay = initialDelay / level;
  showLevel(level);
  startGame();
  
  int counter = 0;

  while(digitalRead(BUTTON_PIN) == HIGH) {
    writeLeds(ledAnimationSequence[counter]);
    counter++;

    if (counter == ledAnimationLength) {
      counter = 0;
    }

    delay(currentDelay);
  }

  showResult(counter);

  if (counter == BUTTON_LED_NUMBER - 1) {
    Serial.println("WON!");
    level++;
  } else {
    Serial.println("LOST!");
    level = 1;
  }

}


void startGame() {
  for (int i = 0; i < startAnimationLength; i++) {
    writeLeds(startAnimationSequence[i]);
    delay(1000);
  }
}

void writeLeds(int leds) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, leds);
  digitalWrite(LATCH_PIN, HIGH);
}

void showLevel(int level) {
  writeLeds(ledAnimationSequence[level - 1]);
  delay(1000);
  writeLeds(0);
  delay(200);
}

void showResult(int counter) {
  for (int i = 0; i < 3; i++) {
    writeLeds(ledAnimationSequence[counter]);
    delay(200);
    writeLeds(0);
    delay(200);
  }
}
