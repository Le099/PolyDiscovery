#include <HCSR04.h>

// HCSR04 init
#define trigPin 2
#define echoPin 3
UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);

// Motor init
#define enA 10 // Right motor speed handler pin
#define in1 9 // First rotation handler pin
#define in2 8 // Second rotation handler pin
#define enB 13 // Left motor
#define in3 12 // First rotation handler pin
#define in4 11 // Second rotation handler pin
int vitesse = 100;

// Joystick init
#define sw 6 // Switch two positions
#define VRx 0 // X
#define VRy 1 // Y

// IR sensors init
#define IR_F 25 // front
#define IR_F_L 23 // front left
#define IR_F_R 27 // front right
#define IR_B_L 31 // back left
#define IR_B_R 29 // back right
int detection = HIGH; // no obstacle

int speed = 0;

void setup() 
{
  // Motor setup
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  //Mode setup
  pinMode(sw, INPUT);
  // IR sensors setup
  pinMode(IR_F, INPUT);
  pinMode(IR_F_L, INPUT);
  pinMode(IR_F_R, INPUT);
  pinMode(IR_B_L, INPUT);
  pinMode(IR_B_R, INPUT);
  
  Serial.begin(9600);
}

void loop() 
{
  while(digitalRead(sw) == HIGH){

    int joy_x = analogRead(VRx);
    int joy_y = analogRead(VRy);

    if((joy_x >= 460 && joy_x <= 540) && (joy_y >= 460 && joy_y <= 540)){ // stop
      leftMotor(0,true);
      rightMotor(0,true);
    }
    else if(joy_y > 1000 && (joy_x >= 460 && joy_x <= 540)) { // left
      leftMotor(100,false);
      rightMotor(100,true);
    }
    else if(joy_y < 20 && (joy_x >= 460 && joy_x <= 540)) { // right
      leftMotor(100,true);
      rightMotor(100,false);
    }
    else if(joy_x > 520 && (joy_y >= 460 && joy_y <= 540)){ // forward
      int vitesse = map(joy_x,520,1023,0,255);
      if(!((digitalRead(IR_F) == LOW) || (digitalRead(IR_F_L) == LOW) || (digitalRead(IR_F_R) == LOW))){ // if no obstacle is in sight in front
        leftMotor(vitesse,true);
        rightMotor(vitesse,true);
      }
      else{ // if obstacle is in sight
        leftMotor(0,true);
        rightMotor(0,true);
      }
    }
    else if(joy_x < 480 && (joy_y >= 460 && joy_y <= 540)){ // backward
      if(!((digitalRead(IR_B_L) == LOW) || (digitalRead(IR_B_R) == LOW))){ // if no obstacle is in sight in the back
        leftMotor(100,false);
        rightMotor(100,false);
      }
      else{ // if obstacle is in sight
        leftMotor(0,true);
        rightMotor(0,true);
      }
    }
  }
  while(digitalRead(sw) == LOW){
    int joy_x = analogRead(VRx);
    int joy_y = analogRead(VRy);
    if(!((joy_x >= 460 && joy_x <= 540) && (joy_y >= 460 && joy_y <= 540))){ // stop
      stopDelay(2000);
    }
    int frontDistance = distanceSensor.measureDistanceCm();
    Serial.print("Distance front: ");
    Serial.println(frontDistance);
    if(frontDistance > 200){
      speed = 150;
    }else if(frontDistance <= 200 && frontDistance >= 100){
      speed = 100;
    }else if(frontDistance < 100 && frontDistance >= 20){
      speed = 75;
    }else{
      stopDelay(100);
      rightRotation(1000);
      stopDelay(100);
    }
    if(((digitalRead(IR_F) == LOW) &&((digitalRead(IR_F_L) == LOW) || (digitalRead(IR_F_R) == LOW))) && !((digitalRead(IR_B_L) == LOW) || (digitalRead(IR_B_R) == LOW))){
      Serial.println("Small back");
      delay(100);
      leftMotor(100,false);
      rightMotor(100,false);
      delay(1000);
    }
    else if((digitalRead(IR_F_L) == LOW) && (digitalRead(IR_F) == HIGH)){
      Serial.println("Small right");
      stopDelay(100);
      rightRotation(100);
      stopDelay(100);
    }
    else if((digitalRead(IR_F_R) == LOW) && (digitalRead(IR_F) == HIGH)){
      Serial.print("Small left");
      stopDelay(100);
      leftRotation(100);
      stopDelay(100);
    }
    else{
      leftMotor(speed,true);
      rightMotor(speed,true);
    }
  }
}

/**
 * Fonction permettant de faire avancer ou reculer le moteur gauche
 * @param ratio Le pourcentage de puissance a laquelle le moteur doit fonctionner
 * @param sens True: avance, False: recule
 */
void rightMotor(int vitesse,bool sens){
  if(sens){
    digitalWrite(in3,HIGH);      
    digitalWrite(in4,LOW);
    analogWrite(enB,vitesse);
  }
  else {
    digitalWrite(in3,LOW);      
    digitalWrite(in4,HIGH);
    analogWrite(enB,vitesse);
  }
}

/**
 * Fonction permettant de faire avancer ou reculer le moteur droit
 * @param ratio Le pourcentage de puissance a laquelle le moteur doit fonctionner
 * @param sens True: avance, False: recule
 */
void leftMotor(int vitesse, bool sens) {
  if(sens){
    digitalWrite(in1,HIGH);      
    digitalWrite(in2,LOW);
    analogWrite(enA,vitesse);
  }
  else {
    digitalWrite(in1,LOW);      
    digitalWrite(in2,HIGH);
    analogWrite(enA,vitesse);
  }
}

/**
 * Fonction permettant d'effectuer une rotation sur la gauche pendant un temps donné
 * @param delay Le delai de rotation (en ms)
 */
void leftRotation(int del){
  leftMotor(75, true);
  rightMotor(75, false);
  delay(del);
}

/**
 * Fonction permettant d'effectuer une rotation sur la droite pendant un temps donné
 * @param delay Le delai de rotation (en ms)
 */
void rightRotation(int del){
  leftMotor(75, false);
  rightMotor(75, true);
  delay(del);
}

/**
 * Fonction permettant d'effectuer une rotation sur la droite pendant un temps donné
 * @param delay Le delai de rotation (en ms)
 */
void stopDelay(int del){
  leftMotor(0, true);
  rightMotor(0, true);
  delay(del);
}
