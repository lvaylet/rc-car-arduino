int throttlePin = 9;     // pin attached to throttle (DC motor)
int steeringPin = 10;    // pin attached to steering (servo motor)
int throttlePos = 1500;  // initial values for throttle and steering
int steeringPos = 1500;

void setup() {                
  pinMode(throttlePin, OUTPUT);
  pinMode(steeringPin, OUTPUT);
}

void loop() {
  digitalWrite(steeringPin, HIGH);       // start PPM pulse
  delayMicroseconds(steeringPos);        // wait pulse diration
  digitalWrite(steeringPin, LOW);        // complete the pulse
  // IMPORTANT
  // delayMicroseconds() is limited to 16383µs
  // Reference: http://arduino.cc/en/Reference/DelayMicroseconds
  // Hence:
  // delayMicroseconds(20000L-steeringPos);
  // is replaced with:
  delayMicroseconds(5000L-steeringPos);  // adjust to 5ms period
  delay(15);                             // pad out 5ms to 20ms PPM period
}
