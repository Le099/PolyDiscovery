const int sw = 18; // Button on joystick
const int VRx = 0; // X
const int VRy = 1; // Y
bool automaticMode = false; // Interrupt when sw press

void setup() 
{
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
        Serial.println("STOP");
      }
      else if(joy_y > 1000 && (joy_x >= 460 && joy_x <= 540)) { // right
        Serial.println("RIGHT");
      }
      else if(joy_y < 20 && (joy_x >= 460 && joy_x <= 540)) { // left
        Serial.println("LEFT");
      }
      else if(joy_x > 520 && (joy_y >= 460 && joy_y <= 540)){ // forward
        Serial.println("FORWARD");
      }
      else if(joy_x < 480 && (joy_y >= 460 && joy_y <= 540)){ // backward
        Serial.println("BACKWARD");
      }
      delay(250);
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
