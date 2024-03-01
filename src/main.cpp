//////////////////////// Step 3 "Combine obstacle detection and avoidance with line tracking."

////////////////////////  Parameter //////////////////////// 

#include <Arduino.h>
#include <Servo.h>

#define ServoPin 9 //attach pin D9 Arduino to pin of Servo motor
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

#define RightPin 11 //attach pin D11 Arduino to pin of Line tracking right sensor
#define MiddlePin 12 // attach pin D12 Arduino to pin of Line tracking middle sensor
#define LeftPin 10 //attach pin D10 Arduino to pin of Line tracking left sensor

#define LT_R !digitalRead(11)
#define LT_M !digitalRead(12)
#define LT_L !digitalRead(10)

#define ditectDistance 15 //Distance threshold that which an obstacle is first detected
#define avoidDistance 30 //Distance threshold to avoid obstacles 



Servo servo;
int angle; // Current angle
int rightDistance = 0, leftDistance = 0, middleDistance = 0;////Distance that which an obstacle is first detected

int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;     //M1 Direction Control
int M2 = 7;     //M2 Direction Control

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

////////////////////////  Functions for moving the tank //////////////////////// 

void stop(void)  //Stop
{
  digitalWrite(E1,0);
  digitalWrite(M1,LOW);
  digitalWrite(E2,0);
  digitalWrite(M2,LOW);
}

void forward(char a,char b){  //Move forward
  analogWrite (E1,a);    
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
}

void back(char a,char b){  //Move backward
  analogWrite (E1,a);
  digitalWrite(M1,LOW);
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
}

void left(char a,char b){  //Turn Right
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,LOW);

}

void right(char a,char b){  //Turn Left
  analogWrite (E1,a);
  digitalWrite(M1,LOW);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
}

//////////////////////// Functions for Line detectiion //////////////////////// 


void lineDetection() {
    if(LT_M){
      forward(100,100);
    } else if(LT_R) { 
      back(100,100);
      right(120,120);
    } else if(LT_L) {
      back(100,100);
      left(120,120);
    } else if (!LT_M & !LT_L & !LT_R) {
      forward(100,100);
    }
}

//////////////////////// Function for Obstacle detectiion and avoiding //////////////////////// 

int Distance_test() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}  

// Function to move the robot in a given direction for a specified time
void moveAndDelay(void (*moveFunc)(char, char), int speed, int durationMs) {
  moveFunc(speed, speed);
  delay(durationMs);
}

// Function to stop the robot and wait for a specified time
void stopAndWait(int durationMs) {
  stop();
  delay(durationMs);
}

// Function to set servo position, wait, measure, and return the distance
int setServoMeasureDistance(int angle, int waitMs) {
  servo.write(angle);
  delay(waitMs);
  return Distance_test();
}

void avoidRight() {
    stopAndWait(500);
    moveAndDelay(right, 200, 1000);
    stopAndWait(500);
    leftDistance = setServoMeasureDistance(170, 500);

    while (leftDistance < avoidDistance) {
      moveAndDelay(forward, 100, 500);
      stopAndWait(500);                             
      leftDistance = setServoMeasureDistance(170, 500);
    }
    
    int repeatTimes = 1;

    for(int i = 0; i < repeatTimes; i++) {
      stopAndWait(500);  
      moveAndDelay(left, 200, 700);
      stopAndWait(500);
      moveAndDelay(forward, 100,3000);
      leftDistance = setServoMeasureDistance(170, 500);

      while (leftDistance < avoidDistance) {
          moveAndDelay(forward, 100, 500);
          stopAndWait(500);                   
          leftDistance = setServoMeasureDistance(170,500);   
      }
    }

    servo.write(90);  //setservo position according to scaled value
    stopAndWait(500); 
    moveAndDelay(left, 200, 600);
    stopAndWait(500);

    while (!LT_M & !LT_L & !LT_R) {
        moveAndDelay(forward, 100, 100);
    }
    lineDetection();
    
}

void avoidLeft(){
    stopAndWait(500);
    moveAndDelay(left, 200, 1000);
    stopAndWait(500);
    leftDistance = setServoMeasureDistance(10, 500);

    while (leftDistance < avoidDistance) {
      moveAndDelay(forward, 100, 500);
      stopAndWait(500);                             
      leftDistance = setServoMeasureDistance(10, 500);
    }
    
    int repeatTimes = 1;

    for(int i = 0; i < repeatTimes; i++) {
      stopAndWait(500);  
      moveAndDelay(right, 200, 800);
      stopAndWait(500);
      moveAndDelay(forward, 100,3000);
      leftDistance = setServoMeasureDistance(10, 500);

      while (leftDistance < avoidDistance) {
          moveAndDelay(forward, 100, 500);
          stopAndWait(500);                   
          leftDistance = setServoMeasureDistance(10,500);   
      }
    }

    servo.write(90);  //setservo position according to scaled value
    stopAndWait(500); 
    moveAndDelay(right, 200, 600);
    stopAndWait(500);

    while (!LT_M & !LT_L & !LT_R) {
        moveAndDelay(forward, 100, 100);
    }
    lineDetection();
}

void ObjectDetection(int middleDistance){
    if(middleDistance <= ditectDistance) {     
      stopAndWait(500);                        
      servo.write(10);  //right        
      delay(1000);      
      rightDistance = Distance_test();
      
      delay(500);
      servo.write(90);  //front            
      delay(1000);                                                  
      servo.write(170);  //left            
      delay(1000); 
      leftDistance = Distance_test();
      
      delay(500);
      servo.write(90);   //front           
      delay(1000);

      if(rightDistance > leftDistance) {
        moveAndDelay(back, 150, 500);
        avoidRight();
      }
      else if(rightDistance < leftDistance) {
        moveAndDelay(back, 150, 500); 
        avoidLeft();
      }
      else if((rightDistance <= ditectDistance) || (leftDistance <= ditectDistance)) {
        moveAndDelay(back, 150, 500); 
        avoidRight();
      }
      else {
        lineDetection();
      }
    }  
    else {
      lineDetection();
    }  
}

void setup(void){
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  servo.attach(ServoPin); // Attach servo to pin 9

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  pinMode(RightPin, INPUT); // Sets the RightPin as an INPUT
  pinMode(MiddlePin, INPUT); // Sets the MiddlePin as an INPUT
  pinMode(LeftPin, INPUT); // Sets the LeftPin as an INPUT
  
  stop(); // Set Stop Main Motor  
  servo.write(90);  //setservo position according to scaled value
  delay(3000);
}

void loop() {
    middleDistance = Distance_test();
    ObjectDetection(middleDistance);
}