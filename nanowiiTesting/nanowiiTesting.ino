/*
int pin = 1;  //GPIO1
void setup() {
PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_GPIO1); //use pin as GPIO1 instead of UART TXD
gpio_output_set(0, 0, 1 << pin, 0); // enable pin as output
}

void loop() {

gpio_output_set(1 << pin, 0, 0, 0); // set pin high

delay(500);

gpio_output_set(0, 1 << pin, 0, 0); // set pin low
}
*/

const int LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(500);
  Serial.println("Interval");
  digitalWrite(LED, LOW);
  delay(500);
}



