Qconst int INPIN = A1;
const int LEDPIN = 3;
volatile int soundIn;
volatile int soundOut;
volatile int baseLine = 0;

unsigned long lastSoundDetect;
int soundAlarmTime = 10;

void setup() {
  Serial.begin(9600);
  pinMode(INPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  for (int i = 0; i < 400; i++) {
      baseLine += map(analogRead(INPIN), 0, 1023, 0, 255);
      delay(50);
  }
  baseLine = baseLine / 400;
}

void loop() {
  soundIn = analogRead(INPIN);
  soundOut = map(soundIn, 0, 1023, 0, 255) - baseLine;
  analogWrite(LEDPIN, soundOut);
  delay(2);
  //Serial.println(soundIn);
  /*soundDetect = digitalRead(INPIN);
  if (soundDetect == LOW) {
    lastSoundDetect = millis();
    if (!bAlarm) {
      bAlarm = true;
      digitalWrite(LEDPIN, HIGH);
    }  
  } else {
    if((millis() - lastSoundDetect) > soundAlarmTime && bAlarm) {
      bAlarm = false;
      digitalWrite(LEDPIN, LOW);
    }
  }*/
}
