const int segmentPins[] = {19, 18, 17, 16, 15, 14, 13};

const int digitCommonPins[] = {2, 4, 5};

const byte digitPatterns[][7] = {
  {1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1}
};

int currentNumber = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting 3-digit counter 000-999 (Multiplexed)...");

  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(digitCommonPins[i], OUTPUT);
    digitalWrite(digitCommonPins[i], HIGH);
  }
}

void writeSegments(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digitPatterns[digit][i]);
  }
}

void clearSegments() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
  }
}

void loop() {
  static unsigned long lastCountTime = 0;
  unsigned long currentTime = millis();
  const unsigned long countInterval = 500;

  if (currentTime - lastCountTime >= countInterval) {
    currentNumber++;
    if (currentNumber > 999) {
      currentNumber = 0;
    }
    Serial.print("Current Number: ");
    Serial.println(currentNumber);
    lastCountTime = currentTime;
  }

  int units = currentNumber % 10;
  int tens = (currentNumber / 10) % 10;
  int hundreds = currentNumber / 100;

  clearSegments();
  digitalWrite(digitCommonPins[0], LOW);
  writeSegments(units);
  delay(3);
  digitalWrite(digitCommonPins[0], HIGH);

  clearSegments();
  digitalWrite(digitCommonPins[1], LOW);
  writeSegments(tens);
  delay(3);
  digitalWrite(digitCommonPins[1], HIGH);

  clearSegments();
  digitalWrite(digitCommonPins[2], LOW);
  writeSegments(hundreds);
  delay(3);
  digitalWrite(digitCommonPins[2], HIGH);
}
