#define SAFE

//------PID Config--------
#define ROLL_KP 0.000
#define ROLL_KI 0.000
#define ROLL_KD 0.000
#define ROLL_KMIN -200.0
#define ROLL_KMAX 200.0

#define PITCH_KP 0.000
#define PITCH_KI 0.000
#define PITCH_KD 0.000
#define PITCH_KMIN -200.0
#define PITCH_KMAX 200.0

#define YAW_KP 0.000
#define YAW_KI 0.000
#define YAW_KD 0.000
#define YAW_KMIN 100.0 //-100.0??
#define YAW_KMAX 100.0

//------------------------

//------RX Config---------
#define THR_RMIN 1000
#define THR_SAFE_SHUTOFF 1120
#define THR_RMAX 1900
#define THR_RMID 1470

#define ROLL_RMIN THR_RMIN
#define ROLL_RMAX THR_RMAX
#define ROLL_WMIN -30
#define ROLL_WMAX 30

#define PITCH_RMIN THR_RMIN
#define PITCH_RMAX THR_RMAX
#define PITCH_WMIN -30
#define PITCH_WMAX 30

#define YAW_RMIN THR_RMIN
#define YAW_RMAX THR_RMAX
#define YAW_WMIN -30
#define YAW_WMAX 30

//------------------------

//------IMU Config--------
// Not sure if it is needed if using an integrated mpu

//------Debug Config------
#define DEBUG_OUTPUT
#define DEBUG_ANGLES
#define DEBUG_PID
#define DEBUG_RX
#define DEBUG_MOTORS
#define DEBUG_LOOP_TIME

//------------------------

//------Motor PWM Levels--
#define MOTOR_MIN_LEVEL 1000
#define MOTOR_ARM_LEVEL 1100
#define MOTOR_MAX_LEVEL 2000

//------RX Pins-----------
//#define RX_PINS_OFFSET 2
#define PIN_RX_ROLL 2
#define PIN_RX_PITCH 3
#define PIN_RX_THR 4
#define PIN_RX_YAW 5

//------Motor Pins--------
#define PIN_M0  6
#define PIN_M1  9
#define PIN_M2  10
#define PIN_M3  11

//------LED Pins----------
#define PIN_LED 13



