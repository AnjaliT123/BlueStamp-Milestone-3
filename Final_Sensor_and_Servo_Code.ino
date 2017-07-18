#include <Servo.h>
//PIN 10 HAS BROKEN WIRE IN IT. PIN 5 DOES TOO


//one pin for the IR emitters, and 4 pins for each detector
int IRemitter = 3;
int IRdetectorfr = 6;
int IRdetectorfl = 7;
int IRdetectorbr = 4;
int IRdetectorbl = 11;

//each distance reads 1 or 0, where 1 means the wave was detected, and 0 means the wave wasn't detected
int distancefr;
int distancefl;
int distancebr;
int distancebl;

//a delay so that the servos have time to react to the changes
int driveDelay = 100;

Servo leftServo;
Servo rightServo;

void setup() {
  //for testing purposes, use the built in LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(IRemitter, OUTPUT);
  digitalWrite(IRemitter, HIGH);
  
  pinMode(IRdetectorfr, INPUT);
  pinMode(IRdetectorfl, INPUT);
  pinMode(IRdetectorbr, INPUT);
  pinMode(IRdetectorbl, INPUT);
  
  Serial.begin(9600);


  rightServo.attach(9);
  leftServo.attach(12);
  rightServo.write(90);   //no movement on this servo
  leftServo.write(90);    //no movement
  
}

void loop() {
  distancefr = readIR(IRdetectorfr); //read from the detector 
  distancefl = readIR(IRdetectorfl);
  distancebr = readIR(IRdetectorbr); //read from the detector 
  distancebl = readIR(IRdetectorbl);
  Serial.print(distancefr);
  Serial.print("\t");
  Serial.print(distancefl);
  Serial.print("\t");
  Serial.print(distancebr);
  Serial.print("\t");
  Serial.println(distancebl);


  //if the front two sensors are hanging off the edge, reverse straight back
  if(distancefr==1 && distancefl==1){
    stop();
    delay(driveDelay);
    reverse();
    delay(driveDelay*3);
  }

  //if the back two sensors are hanging off the edge, drive straight forward
  else if(distancebr==1 && distancebl==1){
    stop();
    delay(driveDelay);
    goForward();
    delay(driveDelay*3);
  }

  
  else if(distancefr==1){
    stop();
    delay(driveDelay);
    reverseRight();
    delay(driveDelay*3);
  }

  else if(distancefl==1){
    stop();
    delay(driveDelay);
    reverseLeft();
    delay(driveDelay*3);
  }

  else if(distancebr==1){
    stop();
    delay(driveDelay);
    forwardLeft();
    delay(driveDelay*3);
  }

  else if(distancebl==1){
    stop();
    delay(driveDelay);
    forwardRight();
    delay(driveDelay*3);
  }

  else{
    goForward();
    delay(driveDelay);
  }
  
  delay(100);

}

//stops the robot completely
void stop(){
  leftServo.write(90);
  rightServo.write(90);
  
}

//drive straight forward
void goForward(){
  leftServo.write(0);
  rightServo.write(180);
}

//reverse straight back
void reverse(){
  leftServo.write(180);
  rightServo.write(0);
}

//goes forward while turning left
void forwardLeft(){
  leftServo.write(0);
  rightServo.write(90);
}

//goes forward while turning right
void forwardRight(){
  rightServo.write(180);
  leftServo.write(90);
}

//reverses while turning left
void reverseLeft(){
  rightServo.write(0);
  leftServo.write(90);
  
}

//reverses while turning right
void reverseRight(){
  leftServo.write(180);
  rightServo.write(90);
}



//reads the IR from the detector
int readIR(int IRdetector){
  tone(IRemitter, 38000, 8);
  delay(1);
  int ir = digitalRead(IRdetector); //0 means wave detected, 1 means not
  delay(1);
  return ir;
 
}
  


