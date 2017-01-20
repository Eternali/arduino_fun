#define PIN_ROLL 1
#define PIN_PIT  3
#define PIN_THR  8
#define PIN_YAW  12

volatile unsigned long timer_start;
volatile int last_interrupt;

void calcSig(int pin) {

  last_interrupt = micros();

  if (digitalRead(pin) == HIGH) {
    timer_start = micros();  
  } else {
    if (timer_start != 0) {
      pulse_time = ((volatile int) micros() - timer_start);
      timer_start = 0;  
    }  
  }
  
}

void setup() {

  timer_start = 0;
  attachInterrupt(PIN_ROLL, calcSig(PIN_ROLL), CHANGE);
  //attachInterrupt(PIN_PIT,  calcSig(PIN_PIT),  CHANGE);
  //attachInterrupt(PIN_THR,  calcSig(PIN_THR),  CHANGE);
  //attachInterrupt(PIN_YAW,  calcSig(PIN_YAW),  CHANGE);

  Serial.begin(115200);
  while(!Serial);
  
}

void loop() {

  Serial.println(pulse_time);
  delay(20);
  
}



