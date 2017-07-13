void init_rx() {

  pinMode(PIN_ROLL,  INPUT);
  pinMode(PIN_PITCH, INPUT);
  pinMode(PIN_THR,   INPUT);
  pinMode(PIN_YAW,   INPUT);

  enableInterrupt(PIN_ROLL,  calc_roll,  CHANGE);
  enableInterrupt(PIN_PITCH, calc_pitch, CHANGE);
  enableInterrupt(PIN_THR,   calc_thr,   CHANGE);
  enableInterrupt(PIN_YAW,   calc_yaw,   CHANGE);
  
}

void calc_roll()  { calc_input(ROLL,  PIN_ROLL);  }
void calc_pitch() { calc_input(PITCH, PIN_PITCH); }
void calc_thr()   { calc_input(THR,   PIN_THR);   }
void calc_yaw()   { calc_input(YAW,   PIN_YAW);   }

void rx_read_values() {
  noInterrupts();
  memcpy(rx_values, (const void *)rx_shared, sizeof(rx_shared));
  interrupts();  
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
      rx_start[channel] = micros();
  } else {
    uint16_t rx_compare = (uint16_t)(micros() - rx_start[channel]);
    rx_shared[channel] = rx_compare;  
  }
}

void update_rx() {

  rx_read_values();

  Serial.print("ROLL: ");  Serial.print(rx_values[ROLL]);  Serial.print('\t');
  Serial.print("PITCH: "); Serial.print(rx_values[PITCH]); Serial.print('\t');
  Serial.print("THR: ");   Serial.print(rx_values[THR]);   Serial.print('\t');
  Serial.print("YAW: ");   Serial.print(rx_values[YAW]);   Serial.print('\n');

  delay(100);
  
}
