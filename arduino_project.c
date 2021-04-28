/*
Student name: Tatek Yizhak
ID: 304352875
*/
#include <Servo.h>
int a=0;
Servo myServo;
int servoPin = A0;
int angle;

//Ultrasonic            
typedef struct {
  int trig ;
  int echo ;
  long duration;
  long distance;
}Ultrasonic_sensor; 

// Motor A connections
int enA = 11;
int in1A = 8;
int in2A = 7;
// Motor B connections
int enB = 3;
int in3B = 5;
int in4B = 4;

void acceleration_backward() {
    // Now change motors directions
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, HIGH);
    
    digitalWrite(in3B, LOW);
    digitalWrite(in4B, HIGH);
    
    delay(1000);
    //  speed Accelerate Motor A & B
    analogWrite(enA, 150);
    analogWrite(enB, 150);
  
  // Turn off motors
//  digitalWrite(in1A, LOW);
//  digitalWrite(in2A, LOW);
//  digitalWrite(in3B, LOW);
//  digitalWrite(in4B, LOW);
}

void acceleration_forward() {
  // Turn on Motor A
  digitalWrite(in1A, HIGH);
  digitalWrite(in2A, LOW );
  // Turn on Motor B
  digitalWrite(in3B, HIGH);
  digitalWrite(in4B, LOW);
  
  delay(1000);
  //  speed Accelerate Motor A & B
    analogWrite(enA, 150);
    analogWrite(enB, 150);
    
  // Now turn off motors
//  digitalWrite(in1A, LOW);
//  digitalWrite(in2A, LOW);
//  digitalWrite(in3B, LOW);
//  digitalWrite(in4B, LOW);
}
void TurnOFFmotors() {
  //  Stop speed Accelerate Motor A & B
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  
    delay(80);
  // Turn off motors
  digitalWrite(in1A, LOW);
  digitalWrite(in2A, LOW);
  digitalWrite(in3B, LOW);
  digitalWrite(in4B, LOW);
}

int neck_angle_rotation(){
    delay(1000);
   for(angle = 90; angle <= 180; angle +=5)  // goes from 0 degrees to 180 degrees
    {                                  // in steps of 10 degrees
      myServo.write(angle);              // tell servo to go to angleition in variable 'angle'
      delay(200); //delay so that servo reach new angleition - depends on step - experiment with speed; 
    }
    for(angle = 180; angle>=0; angle-=5)     // goes from 180 degrees to 0 degrees
    {                               
      myServo.write(angle);              // tell servo to go to angleition in variable 'angle'
       delay(200); //delay so that servo reach new angleition - depends on step - experiment with speed;
    }
}

void turn_right()
{
   digitalWrite(in1A,HIGH);//right motor forward
   digitalWrite(in2A,LOW);
   digitalWrite(in3B,LOW);//left motor bckward
   digitalWrite(in4B,HIGH);
   myServo.write(90);
   analogWrite(enA,100);
   analogWrite(enB,80);
   //Serial.println(x);
   delay(90);//so that the condition for stopping is not reached before it even starts turning
}

void turn_left()
{
   digitalWrite(in1A,LOW);//right motor bckward
   digitalWrite(in2A,HIGH);
   digitalWrite(in3B,HIGH);//left motor forward
   digitalWrite(in4B,LOW);
   
   analogWrite(enA,80);
   analogWrite(enB,100);
   //Serial.println(x);
   delay(80);//so that the condition for stopping is not reached before it even starts turning
}


void setup () {
  
  Serial.begin(9600);  
            
  Ultrasonic_sensor trigPin ,echoPin;
  pinMode(trigPin.trig,OUTPUT);       
  pinMode(echoPin.echo, INPUT);

  myServo.attach(servoPin);
  neck_angle_rotation();
      myServo.write(90); 
      delay(200);

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT); pinMode(in1A, OUTPUT); pinMode(in2A, OUTPUT);
  pinMode(enB, OUTPUT); pinMode(in3B, OUTPUT); pinMode(in4B, OUTPUT);
}
void loop() {
  int x;
  Ultrasonic_sensor measure_duration, measure_distance, trigPin ,echoPin;
  trigPin.trig=13;
  echoPin.echo=12;
  
  // Turn off motors - Initial state
  digitalWrite(in1A, LOW);digitalWrite(in2A, LOW);digitalWrite(in3B, LOW);digitalWrite(in4B, LOW);
  //====Ultrasonic===
  digitalWrite(trigPin.trig, LOW);                          
  delayMicroseconds(5);                                      
  digitalWrite(trigPin.trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin.trig, LOW);

  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  measure_duration.duration = pulseIn(echoPin.echo, HIGH);
  
  measure_distance.distance =(measure_duration.duration/29.1)/2;
                             
  Serial.println("\t");
   //Serial.println(-a++);
   if (measure_distance.distance > 60) 
    {
      acceleration_forward();
       //x = neck_angle_rotation(); 
      Serial.println(measure_distance.distance);
      //turn_left(measure_distance.distance);

//        for(angle = 90; angle <= 180; angle +=3)  // goes from 0 degrees to 180 degrees
//        {                                  // in steps of 10 degrees
//          myServo.write(angle);              // tell servo to go to angleition in variable 'angle'
//          delay(200); //delay so that servo reach new angleition - depends on step - experiment with speed;
//          if(measure_distance.distance >= 80 && measure_distance.distance <= 90)
//          {
//            myServo.write(90); 
//            delay(200);
//            turn_left();
//            Serial.println(measure_distance.distance);
//            
//          }
//        }
//        for(angle = 180; angle>=0; angle-=3)     // goes from 180 degrees to 0 degrees
//        {                               
//          myServo.write(angle);              // tell servo to go to angleition in variable 'angle'
//           delay(200); //delay so that servo reach new angleition - depends on step - experiment with speed;
//           if(measure_distance.distance >= 80 && measure_distance.distance <= 90)
//            {
//              myServo.write(90); 
//              delay(200);
//              turn_right();
//              Serial.println(-measure_distance.distance);
//              
//            }
//        }
    }
    else if(measure_distance.distance<40) 
    {
       acceleration_backward();
       //turn_left(-measure_distance.distance);
      Serial.println(-measure_distance.distance); 
    }
    else if (measure_distance.distance >= 40 && measure_distance.distance <= 60) 
    {
       // Turn off motors
       myServo.write(90);
       TurnOFFmotors();
      Serial.println(measure_distance.distance);
    }
//    else if(measure_distance.distance >= 60 && measure_distance.distance <= 80)
//    {
//      myServo.write(90);
//      acceleration_forward();
//      Serial.println(measure_distance.distance);
//    }
//    else if(x >= 80 && x <= 90)
//    {
//      Serial.println(measure_distance.distance);
//      acceleration_forward();
//    }
//    
  delay(30);
}

