// Ultrasonic Sensor Pins
const int trigPin = 7;  // Trigger pin
const int echoPin = 8;  // Echo pin

// Motor Driver Pins
const int enA = 10; // Motor speed control (PWM)
const int in1 = 9;  // Motor direction control

// LED Pins
const int grnPin = 6; // Green LED
const int redPin = 5; // Red LED

// Distance Threshold (in cm)
const int DIST_THRESHOLD = 50;

void setup() {
  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set motor driver pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);

  // Set LED pins
  pinMode(grnPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  // Set first state for components
  digitalWrite(in1, HIGH);    // Motor runs forward
  analogWrite(enA, 128);      // Motor at 50% speed
  digitalWrite(grnPin, HIGH); // Green LED ON
  digitalWrite(redPin, LOW);  // Red LED OFF

  Serial.begin(9600); // Start serial monitor for debugging
}

void loop() {
  long distance = measureDistance();

  if (distance < DIST_THRESHOLD) {
    // Object is close: Motor runs, Green LED ON
    digitalWrite(in1, HIGH);    // Motor forward
    analogWrite(enA, 128);      // Motor at 50% speed
    digitalWrite(grnPin, HIGH); // Green LED ON
    digitalWrite(redPin, LOW);  // Red LED OFF
  } else {
    // Object is far: Motor stops, Red LED ON
    digitalWrite(in1, LOW);     // Motor stopped
    analogWrite(enA, 0);        // Motor speed 0
    digitalWrite(grnPin, LOW);  // Green LED OFF
    digitalWrite(redPin, HIGH); // Red LED ON
  }

  delay(100); // Small delay for stability
}

// Function to measure distance using ultrasonic sensor
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}
