// Simple demonstration of how to control two motors using an h-bridge (L293D) and arduino uno
// Author: Conrad Heidebrecht, December 2016

// declare pins being used
const int enPin1 = 11;          // enable pin for motor 1
const int enPin2 = 6;          // enable pin for motor 2
const int inPin1 = 10;          // input pin 1 for motor 1
const int inPin2 = 9;           // input pin 2 for motor 1
const int inPin3 = 5;           // input pin 1 for motor 2
const int inPin4 = 3;           // input pin 2 for motor 2
const int switchPin1 = 4;       // switch pin for motor 1
const int switchPin2 = 2;       // switch pin for motor 2
//const int potPin1 = 0;          // potential (analog) pin for motor 1
//const int potPin2 = 1;          // potential (analog) pin for motor 2

void setup () {
  // set pin modes
  pinMode(enPin1, OUTPUT);
  pinMode(enPin2, OUTPUT);
  pinMode(inPin1, OUTPUT);
  pinMode(inPin2, OUTPUT);
  pinMode(inPin3, OUTPUT);
  pinMode(inPin4, OUTPUT);
  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);

  // begin serial monitor
  Serial.begin(9600);
}

void loop () {
  
  //// Motor 1
  // read desired speed from potentiometer1 (divide by 4 because analogRead is 0-1024, h-bridge requires 0-255)
  int speed1 = 100; //analogRead(potPin1) / 4;
  // Reverse the direction of motor using switchpin1
  boolean reverse1 = digitalRead(switchPin1);
  // set the speed of motor 1
  setMotor(speed1, reverse1, 1);

  //// Motor 2
  int speed2 = 100; //analogRead(potPin2) / 4;
  boolean reverse2 = digitalRead(switchPin2);
  setMotor(speed2, reverse2, 2);
  
}

// function to set the speed and direction of a given motor
void setMotor (int speed, boolean reverse, int motor) {
  // variable declaration
  int enPin;
  int in1;
  int in2;

  // set variables according to motor number
  if (motor == 1) {
    enPin = enPin1;
    in1 = inPin1;
    in2 = inPin2;
  } else {
    enPin = enPin2;
    in1 = inPin3;
    in2 = inPin4;
  }

  // set the speed and direction of the motor using H-Bridge
  analogWrite(enPin, speed);
  digitalWrite(in1, !reverse);
  digitalWrite(in2, reverse);
}






