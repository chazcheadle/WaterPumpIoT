/**
 * Water Pump Run Time
 *
 * This sketch is for indicating when a water pump starts
 * and stops running.
 */

// These constants won't change:
const int xPin = A2;            // Accelerometer X pin
const int yPin = A3;            // Accelerometer Y pin
const int indicatorLedPin = 13; // Activity indicator
const int buttonPin = 12;       // Button pin

// Accelerometer configuration:
// TODO: Maybe use trim pots to adjust sensitivity.
int xMin = 0;          // minimum X value
int xMax = 1024;       // maximum X value
int yMin = 0;          // minimum Y value
int yMax = 1024;       // maximum Y value
int activityThreshold = 500; // 500 milliseconds

void setup() {
  // set the LED pins as outputs and the sensor pin as input:
  pinMode(indicatorLedPin, OUTPUT);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT);
  delay(1000);
  calibrateSensor();
}

// Calibrate the sensor.
void calibrateSensor() {
  // Allow sensor to settle.
  delay(1000);
  // blink 3 times.
  xMin = analogeRead(xPin);
  yMin = analogeRead(yPin);
}

// Check for sustained activity.
boolean checkMotion() {
  boolean motion=false;
  if (analogeRead(xPin) > xMin || analogRead(yPin) > yMin) {
    motion=true;
    return motion;
  }
}

void loop() {
  // Recalibrate the sensor.
  if (analogRead(buttonPin) > 500) {
    calibrateSensor();
  }

  if (checkMotion()) {
    delay(activityThreshold);
    // Check to see if pump is actually running.
    if (checkMotion())
      Serial.print("Water pump turned ON");
      digitalWrite(indicatorLedPin, HIGH);
      // Continue to check pump state.
      do {
        delay(50);
      } while (checkMotion());
      // When pump stops running, send a notification.
      Serial.print("Water pump turned OFF");
      digitalWrite(indicatorLedPin, LOW);
    }
  }
}
