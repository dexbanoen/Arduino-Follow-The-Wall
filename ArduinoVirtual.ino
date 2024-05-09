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

// ENTER SECTION

if(distance > 120 ) // This is the code approaching the wall so it can enter a certain distance.
  {
     leftservo.write(145); // Slight turn towards the wall.
     rightservo.write(0);
  }

// FIRST WALL SECTION
  if(distance > 80 && distance < 120) // Within these distances, the system will attempt to move along the wall and keep parallel using a zig-zag pattern.
  { 
     leftservo.write(200);
     rightservo.write(87);
     delay(300); // Slight turn to the right with respect to the face of the system.
     leftservo.write(110);
     rightservo.write(10);
     delay(300);// Slight turn to the left with respect to the face of the system. (Zig-Zag Movement)
  }

// SHARP TURN SECTION
    if(distance > 180) // At this distance, once it does not detect a wall, hence a distance above 180, there will be a sharp turn. The system will roughly attempt to do a 90 degree turn.
  {
     leftservo.write(90);
     rightservo.write(90);
     delay(1);// Stops briefly for any wall detection.
     leftservo.write(200);
     rightservo.write(87);
     delay(200);// System turns slightly away from first wall to setup sharper turn.
     leftservo.write(180);
     rightservo.write(0);
     delay(300); // Goes foward just for slight microadjustment, very small but important.
     leftservo.write(200);
     rightservo.write(0);
     delay(1400); // System moves foward to setup for the approximate 90 degree angle turn.
     leftservo.write(120);
     rightservo.write(330);
     delay(1400); // System moves back slightly at an angle mimicking the 90 degree angle.
     leftservo.write(200);
     rightservo.write(0);
     delay(100);// System moves foward until it detects another wall.
  }

// TOO CLOSE (EMERGENCY)
      if(distance < 70) // This is the warning distance. Once the system approaches too close to the wall, it will reverse/adjust itself to the correct distance. This is very important as it helps "reset" the position to try again.
  {
     leftservo.write(70);
     rightservo.write(170);

    // System backs up until no longer within danger zone.
   }

// SECOND WALL SECTION
  if(distance > 71 && distance < 80) // These are roughly the appopriate distances for the second wall.
  { 
     leftservo.write(200); 
     rightservo.write(87);
     delay(720); // Slight turn to the left with respect to the face of the system.
     leftservo.write(90);
     rightservo.write(10);
     delay(825); // Slight turn to the right with respect to the face of the system. (Zig-Zag Movement)
}
}