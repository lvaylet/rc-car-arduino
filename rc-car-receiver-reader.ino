/**
 * Reading Remote Control Receiver Values with Arduino.
 *
 * References:
 * - https://ryanboland.com/blog/reading-rc-receiver-values/
 *
 * TODO
 * - Add a `last_update_time` variable which gets updated every time an
 *   interrupt fires. If `last_update_time` has not been updated in 2 seconds,
 *   consider the receiver disconnected and reset the values to 1500.
 * - Add a `constrain` call to ensure that the values are within the expected
 *   range of 1000μs - 2000μs.
 * - If the values that are sent by your receiver are not exactly in the range
 *   of 1000μs - 2000μs, you may want to add some sort of calibration, perhaps
 *   with the arduino `map` function.
 */

#include <EnableInterrupt.h>

#define SERIAL_PORT_SPEED  57600

#define RC_NUM_CHANNELS  4

#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3

#define RC_CH1_INPUT  A0
#define RC_CH2_INPUT  A1
#define RC_CH3_INPUT  A2
#define RC_CH4_INPUT  A3

// Final readings, used outside of the RC code. Pulse width, in microseconds.
uint16_t rc_values[RC_NUM_CHANNELS];
// Keep track of the time that the pulses start, in microseconds.
uint32_t rc_start[RC_NUM_CHANNELS];
// Hold the values for each channel until they can be copied into rc_values[]
// rc_shared is marked volatile because it can be updated from the interrupt
// service routines at any time. We don't want to use this outside of the RC
// RC code exactly because it can be updated at any time.
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

void rc_read_values() {
  // Copy the volatile rc_shared[] values into the rc_values[] array. Prior to
  // copying, disable interrupts to ensure that the interrupts do not trigger
  // and alter the memory as we are trying to read it. Again, the rc_values[]
  // should be used throughout the rest of the program (the non remote control
  // related code).
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    // Leading edge. The pulse has just started. Store the current time for
    // later comparison.
    rc_start[channel] = micros();
  } else {
    // Trailing edge. The pulse has ended. Compare the current time to the value
    // previously stored. The result indicates the position of our transmitter
    // stick. Store the value for reading later.
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

void calc_ch1() { calc_input(RC_CH1, RC_CH1_INPUT); }
void calc_ch2() { calc_input(RC_CH2, RC_CH2_INPUT); }
void calc_ch3() { calc_input(RC_CH3, RC_CH3_INPUT); }
void calc_ch4() { calc_input(RC_CH4, RC_CH4_INPUT); }

void setup() {
  Serial.begin(SERIAL_PORT_SPEED);

  pinMode(RC_CH1_INPUT, INPUT);
  pinMode(RC_CH2_INPUT, INPUT);
  pinMode(RC_CH3_INPUT, INPUT);
  pinMode(RC_CH4_INPUT, INPUT);

  // Enable interrupts and set functions called on high to low, or vice versa
  enableInterrupt(RC_CH1_INPUT, calc_ch1, CHANGE);
  enableInterrupt(RC_CH2_INPUT, calc_ch2, CHANGE);
  enableInterrupt(RC_CH3_INPUT, calc_ch3, CHANGE);
  enableInterrupt(RC_CH4_INPUT, calc_ch4, CHANGE);
}

void loop() {
  rc_read_values();

  Serial.print("CH1:"); Serial.print(rc_values[RC_CH1]); Serial.print("\t");
  Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]); Serial.print("\t");
  Serial.print("CH3:"); Serial.print(rc_values[RC_CH3]); Serial.print("\t");
  Serial.print("CH4:"); Serial.println(rc_values[RC_CH4]);

  delay(200);
}
