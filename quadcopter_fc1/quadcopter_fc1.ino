// Arduino flight controller, for Quadcopters
// Designed for the Arduino Leonardo processor on the nanowii flight controller
// 
// Author: Conrad Heidebrecht

//#include <Math.h>
#include <Servo.h>

#include "Config.h"

// I2Cdev and MPU6050 must be installed as libraries, or the files
// for both classes must be in the include path of project
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

////  INITIAL VARIABLES  ////

// mpu object for gyro and acc
MPU6050 mpu;

// state of PIN_LED
bool blinkState = false;

// MPU control/status variables
bool dmpReady = false;  // true if DMP init was successful
uint8_t mpuIntStatus;   // actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// variables for gravity, gyro, and acc
VectorInt16 acc;        // [x, y, z]          acc sensor measurements
VectorFloat gravity;    // [x, y, z]          gravity vector
float gyro[3];          // [yaw, pitch, roll] yaw/pitch/roll container and gravity vector

// RX signals
int throttle = THR_RMIN;
volatile int rx_values[4];      // ROLL, PITCH, THROTTLE, YAW

// PID variables
double pid_roll_in,  pid_roll_out,  pid_roll_setp =  0;
double pid_pitch_in, pid_pitch_out, pid_pitch_setp = 0;
double pid_yaw_in,   pid_yaw_out,    pid_yaw_setp =   0;

// motors
int m0, m1, m2, m3;             // FL, FR, BR, BL (F: FRONT, B: BACK, R: RIGHT, L: LEFT)

// track loop time
unsigned long prev_time = 0;

////  INTERRUPT DETECTION  ////

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    
  mpuInterrupt = true;

}

////  INITIAL SETUP  ////

void setup() {
  
  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
    
  #ifdef DEBUG_OUTPUT
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Debug Output ON");
    debug_process();
  #endif  

  // Initialize and configure mpu and DMP
  mpu.initialize();
  devStatus = mpu.dmpInitialize();

  // gyro offsets go here
  mpu.setXGyroOffset(GYROX_OFF);
  mpu.setYGyroOffset(GYROY_OFF);
  mpu.setZGyroOffset(GYROZ_OFF);
  mpu.setZAccelOffset(ACCZ_OFF);

  // make sure it worked
  if (devStatus == 0) {
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    Serial.print(F("[!!] DMP Initialization failed, code: "));
    Serial.print(devStatus);  
  }
  
  init_motors();
  init_leds();
  init_rx();
  init_pid();
  arm_motors();

}

void loop() {

  // if initialization failed, exit!
  if (!dmpReady) return;
  
  update_imu();
  update_control();

  #ifdef DEBUG_OUTPUT
    debug_process();
  #endif

  prev_time = micros();

}



