// Include the Servo library
#include <Servo.h>

// Define the Trig and Echo pins for the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;

// Variables for the duration and the calculated distance
long duration;
int distance;

// Create a Servo object to control the servo motor
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT); // Set the Trig pin as an output
  pinMode(echoPin, INPUT);  // Set the Echo pin as an input
  Serial.begin(9600);       // Start the serial communication
  myServo.attach(12);       // Attach the servo to pin 12
}

void loop() {
  // Sweep from 15° to 165° and read distances
  for (int angle = 15; angle <= 165; angle++) {
    myServo.write(angle);  // Move the servo to the current angle
    delay(30);             // Allow the servo to reach the position
    distance = calculateDistance(); // Get the distance from the ultrasonic sensor

    // Send the angle and distance over the serial port
    Serial.print(angle);   // Send the angle
    Serial.print(",");     // Separate angle and distance with a comma
    Serial.print(distance); // Send the distance
    Serial.println(".");   // End the data packet
  }

  // Sweep back from 165° to 15° and read distances
  for (int angle = 165; angle >= 15; angle--) {
    myServo.write(angle);  // Move the servo to the current angle
    delay(30);             // Allow the servo to reach the position
    distance = calculateDistance(); // Get the distance from the ultrasonic sensor

    // Send the angle and distance over the serial port
    Serial.print(angle);   // Send the angle
    Serial.print(",");     // Separate angle and distance with a comma
    Serial.print(distance); // Send the distance
    Serial.println(".");   // End the data packet
  }
}

// Function to calculate the distance using the ultrasonic sensor
int calculateDistance() {
  // Send a 10-microsecond pulse to the Trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time of the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  int calculatedDistance = duration * 0.034 / 2;

  // Limit the distance to 40 cm (return 41 for out of range)
  if (calculatedDistance > 40) {
    return 41; // Out of range
  } else {
    return calculatedDistance;
  }
}

