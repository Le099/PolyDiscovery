#include <HCSR04.h>

// defines pins numbers
const int trigPin = 2;
const int echoPin = 3;
 
// Initialize sensor that uses digital pins trigPin and echoPin
UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);
void setup() {
  // Initializing serial monitor communication to 9600
  Serial.begin(9600);
}
void loop() {
  // Distance measurement every 500 ms and print it on serial monitor
  Serial.println(distanceSensor.measureDistanceCm());
  delay(500);
}
