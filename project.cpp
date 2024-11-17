#include <Servo.h>

Servo myServo;
int mq_sensor = A0;      // Analog pin for gas sensor
byte buzzer = 11;        // Digital pin for buzzer
int led = 4;             // Digital pin for LED
int relay = 2;           // Digital pin for relay
int gas_threshold = 400; // Gas detection threshold

void setup() {
  Serial.begin(9600);         // Initialize serial communication
  myServo.attach(9);          // Attach servo to pin 9
  pinMode(mq_sensor, INPUT);  // Set mq_sensor pin as input
  pinMode(buzzer, OUTPUT);    // Set buzzer pin as output
  pinMode(relay, OUTPUT);     // Set relay pin as output
  pinMode(led, OUTPUT);       // Set led pin as output
  myServo.write(0);           // Change the servo degree
  digitalWrite(led, LOW);     // Turn off LED
  digitalWrite(buzzer, LOW);  // Turn off buzzer
  digitalWrite(relay, HIGH);  // Set relay to initial position
}

void loop() {
  int sensor_data = analogRead(mq_sensor);  // Read gas sensor value
  Serial.println(sensor_data);  // Print sensor value to serial monitor

  if (sensor_data > gas_threshold) {
    myServo.write(35);            // Move servo to cut off gas
    digitalWrite(led, HIGH);      // Turn on LED
    digitalWrite(relay, LOW);     // Activate relay
    analogWrite(buzzer, 200);     // Activate buzzer with a tone
    delay(110);
    analogWrite(buzzer, 100);     // Change buzzer tone
    delay(110);
  } else {
    digitalWrite(led, LOW);       // Turn off LED
    digitalWrite(relay, HIGH);    // Deactivate relay
    analogWrite(buzzer, 0);       // Turn off buzzer
  }
}
