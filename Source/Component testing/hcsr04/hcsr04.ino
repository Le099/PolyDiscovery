#include <HCSR04.h>
#include <LiquidCrystal.h>

// defines pins numbers / definition des broches du capteur
const int trigPin = 2;
const int echoPin = 3;

const int rs = 37, en = 39, d4 = 41, d5 = 43, d6 = 45, d7 = 47;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
// Initialize sensor that uses digital pins trigPin and echoPin / initialisation du capteur avec les broches utilisees.
UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);
void setup() {
  // We initialize serial connection so that we could print values from sensor./ initialisation du port serie a 9600 band pour afficher les valeurs mesurees par le capteur.
  Serial.begin(9600);

  lcd.begin(16, 1);
  analogWrite(8,15);
  // Affiche un message
  lcd.print("");
}
void loop() {
  // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters./ toutes les 500 millisecondes nous faisons une mesure et nous affichons la distance en centimetre sur le port serie.
  Serial.println(distanceSensor.measureDistanceCm());
  delay(500);
  lcd.setCursor(0, 1);// place le curseur au 1er caractère de la 2nde ligne
  lcd.print(distanceSensor.measureDistanceCm());
}
