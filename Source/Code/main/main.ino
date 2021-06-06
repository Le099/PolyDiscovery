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
#define sw 18 // Button on joystick
#define VRx 0 // X
#define VRy 1 // Y
bool automaticMode = false; // Interrupt when sw press

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
  
  // Joystick setup
  pinMode(sw, INPUT_PULLUP);
  attachInterrupt(5, button_ISR, RISING); // Interrupt attach

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
  while(automaticMode == false){
    //code for automatic mode here
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
  while(automaticMode == true){
    int frontDistance = distanceSensor.measureDistanceCm();
    Serial.print("Distance front: ");
    if(frontDistance > 200){
      speed = 255;
    }else if(frontDistance <= 200 && frontDistance >= 100){
      speed = 100
    }else if(frontDistance < 100 && frontDistance >= 50){
      speed = 50;
    }else{
      rightRotation(1000);
    }
    Serial.println(frontDistance);
    if((digitalRead(IR_F) == LOW) || (digitalRead(IR_F_L) == LOW) || (digitalRead(IR_F_R) == LOW) || (digitalRead(IR_B_L) == LOW) || (digitalRead(IR_B_R) == LOW)){
      leftMotor(0,true);
      rightMotor(0,true);
    }
    else{ 
      Serial.println("No obstacle!");
      leftMotor(100,true);
      rightMotor(100,true);
    }
  }
}

void button_ISR()
{
  automaticMode = !automaticMode;
  Serial.println("Changing mode...");
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
void leftRotation(int delay){
  leftMotor(100, false);
  rightMotor(100, true);
  delay(delay);
}

/**
 * Fonction permettant d'effectuer une rotation sur la droite pendant un temps donné
 * @param delay Le delai de rotation (en ms)
 */
void leftRotation(int delay){
  leftMotor(100, true);
  rightMotor(100, false);
  delay(delay);
}
