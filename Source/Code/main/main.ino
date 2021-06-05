// Motor init
#define enA 10 // Right motor speed handler pin
#define in1 9 // First rotation handler pin
#define in2 8 // Second rotation handler pin
#define enB 13 // Left motor
#define in3 12 // First rotation handler pin
#define in4 11 // Second rotation handler pin
const int vitesse = 100;

#define sw 18 // Button on joystick
#define VRx 0 // X
#define VRy 1 // Y
bool automaticMode = false; // Interrupt when sw press

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
  attachInterrupt(digitalPinToInterrupt(sw), button_ISR, RISING); // Interrupt attach
  Serial.begin(9600);
}

void loop() 
{
  while(automaticMode == false){
      Serial.println("Automatic mode disabled");
      //code for automatic mode here
      int joy_x = analogRead(VRx);
      int joy_y = analogRead(VRy);

      if((joy_x >= 460 && joy_x <= 540) && (joy_y >= 460 && joy_y <= 540)){ // stop
        leftMotor(0,true);
        rightMotor(0,true);
      }
      else if(joy_y > 1000 && (joy_x >= 460 && joy_x <= 540)) { // right
        leftMotor(255,true);
        rightMotor(255,false);
      }
      else if(joy_y < 20 && (joy_x >= 460 && joy_x <= 540)) { // left
        leftMotor(255,false);
        rightMotor(255,true);
      }
      else if(joy_x > 520 && (joy_y >= 460 && joy_y <= 540)){ // forward
        int vitesse = map(joy_x,520,1023,0,255);
        leftMotor(vitesse,true);
        rightMotor(vitesse,true);
      }
      else if(joy_x < 480 && (joy_y >= 460 && joy_y <= 540)){ // backward
        int vitesse = map(joy_x,480,0,0,255);
        leftMotor(vitesse,false);
        rightMotor(vitesse,false);
      }
  }
  while(automaticMode == true){
      Serial.println("Automatic mode enabled");
      //code for manual mode here
      delay(250);
  }
}

void button_ISR()
{
  automaticMode = !automaticMode;
}

/**
 * Fonction permettant de faire avancer ou reculer le moteur gauche
 * @param ratio Le pourcentage de puissance a laquelle le moteur doit fonctionner
 * @param sens True: avance, False: recule
 */
void leftMotor(int vitesse,bool sens){
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
void rightMotor(int vitesse, bool sens) {
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
