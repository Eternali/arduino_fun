// Line follower robot using 2 IR photodiodes and 4 IR emitters
// Intened to follow a black line based on input from the IR photodiodes
// Author: Conrad Heidebrecht, December 2016
// Licenced using the GNU Public Licence


// Declare pins being used
const int enPin1 = 12;            // enable pin for motor 1 (used for setting speed of motors)
const int enPin2 = 11;            // enable pin for motor 2
const int inPin1 = 10;            // input pin 1 for motor 1 (used for setting direction of motors)
const int inPin2 = 9;             // input pin 2 for motor 1
const int inPin3 = 8;             // input pin 1 for motor 2
const int inPin4 = 7;             // input pin 2 for motor 2
const int IRpin1 = A0;            // IR photodiode pin 1 
const int IRpin2 = A1;            // IR photodiode pin 2
const int IRemitter = 6;          // IR emitters pin
const int buzzerPin = 5;          // buzzer pin for output info

// Declare initial variables
int ambientIR1;                   // store incoming ambient IR
int ambientIR2;
int whiteIR;                      // store calibrated max and min IR values for line and floor
int blackIR;
int cal[20];
int floorIR1;                     // store IR coming from the floor
int floorIR2;
int value1[10];                   // store IR values
int value2[10];
int reflected1;                   // store the sum of the values measured by the sensor
int reflected2;
int tolerance = 20;               // the variance accepted by the sensor to detect lines
int speed1;                       // speed the motors will spin at (0-255)
int speed2;

// declare a struct for readIR
struct readRet {
  int ref1;
  int ref2;  
};

void setup () {
  // Set pin modes
  pinMode(enPin1, OUTPUT);
  pinMode(enPin2, OUTPUT);
  pinMode(inPin1, OUTPUT);
  pinMode(inPin2, OUTPUT);
  pinMode(inPin3, OUTPUT);
  pinMode(inPin4, OUTPUT);
  pinMode(IRemitter, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize serial monitor
  Serial.begin(9600);

  // initialize IR LED to off
  digitalWrite(IRemitter, LOW);
  // initialize BUILTIN LED to off
  digitalWrite(LED_BUILTIN, LOW);

  // calibrate IR sensors, by detecting max and min IR values (max = white; min = black)
  calibrate(10);

}

void loop () {
  
  // read reflected IR from the sensors, irr1 is from left, irr2 is from right
  auto irr= readIR(10);
  // print sensor values 
  Serial.print("left: ");
  Serial.print(irr.ref1);
  Serial.print("   right: ");
  Serial.print(irr.ref2);
  Serial.print("speed left: ");
  Serial.print(speed1);
  Serial.print("   speed right: ");
  Serial.print(speed2);
  Serial.print('\n');

  // check if sensors detect a line
  if (blackIR - tolerance <= irr.ref1 <= blackIR + tolerance) {
    // the left sensor detects a line, we must turn right a bit to stay on line
    speed1 = 70;
    speed2 = 0;
  }
  if (blackIR - tolerance <= irr.ref2 <= blackIR + tolerance) {
    // the right sensor detects a line, we must turn left a bit to stay on line  
    speed1 = 0;
    speed2 = 70;
  }
  else {
    // neither detect a line so we can continue straight ahead
    speed1 = 100;
    speed2 = 100;
  }

  // set the speeds of the motors
  setMotor(speed1, false, 1);
  setMotor(speed2, false, 2);

}

// function to calibrate the IR readings
// should be called during setup stage
void calibrate (int times) {
  Serial.println("Place both IR sensors over the BACKGROUND");
  Serial.println("Calibration will begin in 5 s at the tone");
  
  delay(5000);
  
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(buzzerPin, HIGH);
  auto background = readIR(times);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(buzzerPin, LOW);
  
  Serial.println("Place both IR sensors over the LINE");
  Serial.println("Calibration will begin in 5 s at the tone");
  
  delay(5000);
  
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(buzzerPin, HIGH);
  auto line = readIR(times);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(buzzerPin, LOW);

  whiteIR = (background.ref1 + background.ref2) / 2;
  blackIR = (line.ref1+ line.ref2) / 2;

  Serial.println("Calibration finished. Place robot such that the line is in between the sensors.");
  Serial.println("You have 5 s, the robot will begin following the line at the tone");

  delay(5000);

  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(buzzerPin, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(buzzerPin, LOW);
}

// function to read the IR of the floor of both sensors
// times is the accuracy of the measurement (up to 10)
readRet readIR (int times) {
  for (int x = 0; x < times; x++) {
    digitalWrite(IRemitter, LOW);
    delay(1);
    ambientIR1 = analogRead(IRpin1);
    ambientIR2 = analogRead(IRpin2);
    digitalWrite(IRemitter, HIGH);
    delay(1);
    floorIR1 = analogRead(IRpin1);
    floorIR2 = analogRead(IRpin2);
    value1[x] = ambientIR1 - floorIR1;
    value2[x] = ambientIR2 - floorIR2;
  }

  for (int x = 0; x < times; x++) {
    reflected1 += value1[x];
    reflected2 += value2[x];
  }

  return {(reflected1/times), (reflected2/times)};
  
}

// function to set the speed and direction of a given motor
void setMotor (int speed, boolean reverse, int motor) {
  // decide which motor is being set
  if (motor == 1) {
    analogWrite(enPin1, speed);
    digitalWrite(inPin1, !reverse);
    digitalWrite(inPin2, reverse);
  } else if ( motor == 2) {
    analogWrite(enPin2, speed);
    digitalWrite(inPin3, !reverse);
    digitalWrite(inPin4, reverse);    
  }
  
}






