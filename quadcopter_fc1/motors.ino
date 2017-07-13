Servo motor0;
Servo motor1;
Servo motor2;
Servo motor3;

void init_motors() {

  motor0.attach(PIN_M0);
  motor1.attach(PIN_M1);
  motor2.attach(PIN_M2);
  motor3.attach(PIN_M3);
  motor0.writeMicroseconds(MOTOR_MIN_LEVEL);
  motor1.writeMicroseconds(MOTOR_MIN_LEVEL);
  motor2.writeMicroseconds(MOTOR_MIN_LEVEL);
  motor3.writeMicroseconds(MOTOR_MIN_LEVEL);  

}

void arm_motors() {

  motor0.writeMicroseconds(MOTOR_ARM_LEVEL);
  motor1.writeMicroseconds(MOTOR_ARM_LEVEL);
  motor2.writeMicroseconds(MOTOR_ARM_LEVEL);
  motor3.writeMicroseconds(MOTOR_ARM_LEVEL);
  
}

void update_motors(unsigned int m0, unsigned int m1, unsigned int m2, unsigned int m3) {
  
  motor0.writeMicroseconds(m0);
  motor1.writeMicroseconds(m1);
  motor2.writeMicroseconds(m2);
  motor3.writeMicroseconds(m3);

}
