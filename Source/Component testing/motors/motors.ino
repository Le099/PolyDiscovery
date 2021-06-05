// Déclaration des variables et des constantes moteur ------------------------------------------------------------------------------------------------------------------------------------
int enA = 10; // Left motor speed
int in1 = 9; // Left motor first way of rotation
int in2 = 8; // Left motor second way of rotation
int enB = 13; // Right motor speed
int in3 = 12; // Right motor first way of rotation
int in4 = 11; // Right motor second way of rotation
const int vitesse = 255;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(in1,HIGH); // Left motor forwards
  digitalWrite(in2,LOW); // Left motor forwards

  //digitalWrite(in1,LOW); // Left motor backwards
  //digitalWrite(in2,HIGH); // Left motor backwards

  //digitalWrite(in3, HIGH); // Right motor forwards
  //digitalWrite(in4, LOW); // Right motor forwards

  digitalWrite(in3,LOW); // Right motor backwards
  digitalWrite(in4,HIGH); // Right motor backwards

  analogWrite(enA,vitesse);
  analogWrite(enB, vitesse);

  delay(100);
}
