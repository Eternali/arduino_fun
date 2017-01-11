void init_leds() {
  
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW); 

}

void led_satus(byte stat) {
  
  digitalWrite(PIN_LED, stat);

}
