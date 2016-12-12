const int buzzPin = 11;

void setup() {
  pinMode(buzzPin, OUTPUT);

}

void loop() {
  tone(buzzPin, 500);
  delay(500);
  noTone(buzzPin);
  delay(500);

}
