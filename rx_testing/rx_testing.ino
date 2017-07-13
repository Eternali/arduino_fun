#include <EnableInterrupt.h>
#include "config.h"

uint16_t rx_values[RX_NUM_CHANNELS];
uint16_t rx_start[RX_NUM_CHANNELS];
volatile uint16_t rx_shared[RX_NUM_CHANNELS];

void setup() {
  
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Debugging is ON!");

  init_rx();
  
}

void loop() {

  update_rx();
  
}
