//1,2,3,4

#include <Servo.h>
Servo leftservo;  
Servo rightservo;  
const int pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
void setup() {
  leftservo.attach(9);  
  rightservo.attach(10);
   //set up the Serial
  Serial.begin(9600);
  //setup the pin modes  
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  leftservo.write(90);
  rightservo.write(90);
}
void loop() {
  long duration;  
  //clear the ping pin
  long distance;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  //send the 10 microsecond trigger
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  //get the pulse duration in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
  Serial.print("Distance from the object = ");
  Serial.print(distance);
  Serial.println("cm");

//ENTER SECTION


if(distance > 120 && distance < 180) // This is the code approaching the wall so it can enter a certain distance.
  {
     leftservo.write(145);
     rightservo.write(0);
  }

//FIRST WALL SECTION/ SECOND WALL SECTION


  if(distance > 20 && distance < 40) // Within these distances, the system will attempt to move along the wall and keep parallel using a zig-zag pattern.
  { 
     leftservo.write(200);
     rightservo.write(87);
     delay(200);
     leftservo.write(99);
     rightservo.write(50);
     delay(180);
  }

//TOO CLOSE (EMERGENCY) // This is the warning distance. Once the system approaches too close to the wall, it will reverse/adjust itself to the correct distance. This is very important as it helps "reset" the position to try again.


  if(distance < 20 ) 
  {
     leftservo.write(70);
     rightservo.write(200);
     }


// SHARP TURN SECTION // At this distance, once it does not detect a wall, hence a distance above 180, there will be a sharp turn. The system will roughly attempt to do a 90 degree turn.


         if(distance > 180) 
  {
     leftservo.write(180);
     rightservo.write(0);
     delay(500);
     leftservo.write(120);
     rightservo.write(320);
     delay(1400);
     leftservo.write(200);
     rightservo.write(0);
     delay(100);
  }
     
}