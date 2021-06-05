#define IR_F 25 // front
#define IR_F_L 23 // front left
#define IR_F_R 27 // front right
#define IR_B_L 31 // back left
#define IR_B_R 29 // back right
int detection = HIGH;    // no obstacle
void setup() {
  Serial.begin(9600);   
  pinMode(IR_F, INPUT);
  pinMode(IR_F_L, INPUT);
  pinMode(IR_F_R, INPUT);
  pinMode(IR_B_L, INPUT);
  pinMode(IR_B_R, INPUT);
}
void loop() {  
    if((digitalRead(IR_F) == LOW) || (digitalRead(IR_F_L) == LOW) || (digitalRead(IR_F_R) == LOW) || (digitalRead(IR_B_L) == LOW) || (digitalRead(IR_B_R) == LOW)){
      Serial.println("There is an obstacle!");
      if(digitalRead(IR_F) == LOW) {Serial.print("FRONT ");}
      if(digitalRead(IR_F_L) == LOW) {Serial.print("FRONT_LEFT ");}
      if(digitalRead(IR_F_R) == LOW) {Serial.print("FRONT_RIGHT ");}
      if(digitalRead(IR_B_L) == LOW) {Serial.print("BACK_LEFT ");}
      if(digitalRead(IR_B_R) == LOW) {Serial.print("BACK_RIGHT ");}
      Serial.println("");
    }
    else{ 
      Serial.println("No obstacle!");
    }
    delay(500);
}
