// quadcopter flight controller based from:
// http://www.benripley.com/development/quadcopter-source-code-from-scratch/

// Set motor output power to 50%
Servo motor0;
motor0.attach(PIN_MOTOR0);
int half_power = 1500;
motor0.writeMicroseconds(halfPower);

//// Calculate Roll (angleX), Yaw (angleY), and Pitch (angleZ)  (-180 to +180)

float angleX; 
float angleY;
float angleZ;

// read 12 bytes into data[] from 12C (IMU sensor readings)
// 0 to 3 are Roll
// 4 to 7 are Pitch (? guessing) 
// 8 to 11 are Yaw (? guessing)
Wire.requestFrom(ADDR_SLAVE_12C, PACKET_SIZE);
byte data[PACKET_SIZE];
int i = 0;
while (Wire.available()) {
  data[i] = Wire.read();
  i++;  
}

/// Calculate Roll (angleX)
// Use a union to convert between byte[] (b) and float (fval)
union ROL_tag {byte b[4]; float fval;} ROL_Union;

// Copy the appropriate bytes to Roll union
ROL_Union.b[0] = data[0];
ROL_Union.b[1] = data[1];
ROL_Union.b[2] = data[2];
ROL_Union.b[3] = data[3];

// Copy the float value from union to angle variable
if (isnan(ROL_Union.fval) != 1) {
  angleX = ROL_Union.fval;  
}

/// Calculate Pitch (angleZ)

union PIT_tag {byte c[4]; float gval;} PIT_Union;

PIT_Union.c[0] = data[4];
PIT_Union.c[1] = data[5];
PIT_Union.c[2] = data[6];
PIT_Union.c[3] = data[7];

if (isnan(PIT_Union.gval) != 1) {
  angleZ = PIT_Union.gval;  
}

/// Calculate Yaw (angleY)

union YAW_tag {byte d[4]; float hval;} YAW_Union;

YAW_Union.d[0] = data[8];
YAW_Union.d[1] = data[9];
YAW_Union.d[2] = data[10];
YAW_Union.d[3] = data[11];

if (isnan(YAW_Union.hval) != 1) {
  angleY = YAW_Union.hval;  
}

#include
#define MY_PIN 5  // Could choose any pin here

volatile int pwm_value = 0;
volatile int prev_time = 0;
uint8_t latest_interrupted_pin;

void setup () {
  
}







