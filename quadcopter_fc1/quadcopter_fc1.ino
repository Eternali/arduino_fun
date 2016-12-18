// Arduino flight controller, for Quadcopters
// Designed for the Arduino Leonardo processor on the nanowii flight controller
// 
// Author: Conrad Heidebrecht
// Licenced under the GNU Public Licence

#include "Config.h"
#include <Math.h>
#include <Servo.h>
#include <Wire.h>

//// initial variables

// angle variables for gyro
float angleX, angleY, angleZ = 0.0;

// RX signals
int throttle = THROTTLE_RMIN;
volatile int rx_values[4];      // ROLL, PITCH, THROTTLE, YAW

// PID variables
double pid_roll_in,  pid_roll_out,  pid_roll_setp =  0;
double pid_pitch_in, pid_pitch_out, pid_pitch_setp = 0;
double pid_yaw_in,   pid_yaw_in,    pid_yaw_setp =   0;

// motors
int m0, m1, m2, m3;             // FL, FR, BR, BL (F: FRONT, B: BACK, R: RIGHT, L: LEFT)

// track loop time
unsigned long prev_time = 0;


void setup() {
  #ifdef DEBUG_OUTPUT
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Debug Output ON")
  #endif  

}

void loop() {
  

}
