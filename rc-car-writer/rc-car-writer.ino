/**
 * Writing PPM signals to Electronic Speed Controller (ESC) with Arduino.
 *
 * References:
 * - https://electronics.stackexchange.com/questions/129961/how-to-get-the-pwm-frequency-and-duration-of-each-pulse
 *
 * TODO
 * - Refactor duplicate code with generate_ppm(pin, pos) function
 */

// Pins attached to DC motor (throttle) and servo motor (steering)
int throttlePin = 9;
int steeringPin = 10;

// Initial positions for throttle and steering (= pulse width, in microseconds, usually between 1000 and 2000)
int throttlePos = 1500;
int steeringPos = 1500;

void setup() {
  pinMode(throttlePin, OUTPUT);
  pinMode(steeringPin, OUTPUT);
}

void loop() {
  // Pack the two PPM signals for throttle and steering within a single 20ms frame
  
  // Steering
  digitalWrite(steeringPin, HIGH);        // start PPM pulse
  delayMicroseconds(steeringPos);         // wait pulse duration
  digitalWrite(steeringPin, LOW);         // complete pulse
  delayMicroseconds(10000L-steeringPos);  // pad out to 10ms

  // Throttle
  digitalWrite(throttlePin, HIGH);        // start PPM pulse
  delayMicroseconds(throttlePos);         // wait pulse duration
  digitalWrite(throttlePin, LOW);         // complete pulse
  delayMicroseconds(10000L-throttlePos);  // pad out to 10ms
}
