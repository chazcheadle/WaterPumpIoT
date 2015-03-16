/*
 * Water Pump Run Time
 *
 * This sketch is for indicating when a water pump starts
 * and stops running.
 */

// These constants won't change:
const int sensorPin = A2;       // Accelerometer pin
const int indicatorLedPin = 13; // Activity indicator

// These variables will change:
int sensorMin = 1023;  // minimum sensor value
int sensorMax = 0;     // maximum sensor value
int sensorValue = 0;         // the sensor value

void setup() {
  // set the LED pins as outputs and the sensor pin as input:
  pinMode(indicatorLedPin, OUTPUT);
  pinMode (sensorPin, INPUT);
}

void loop() {
  // while the sensor is vibrating, set state to ON:
  if (analogRead(sensorPin) > sensorMin) {
    // Wait 500ms to ensure pump is running
    delay(500);
    while (analogRead(sensorPin) > sensorMin) {
      digitalWrite(indicatorLedPin, HIGH);
      Serial.send(‘Water pump ON’);
      // Continue checking if sensor is triggered
      delay(500);
    }
    digitalWrite(indicatorLedPin, LOW);
    Serial.send(‘Water pump OFF’);
  }
}
