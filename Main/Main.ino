

int mode = 0;

#include <Ultrasonic.h>
#include <Servo.h> 


Ultrasonic ultrasonic(4,3); // (Trig PIN,Echo PIN)

// Function for sonar reader ============================================================================================================================================================
int readsonar() {
  return ultrasonic.Ranging(CM); // CM or INC;
}

 
// Drivetrain movement command functions =======================================================================================================================
Servo myservo;  // create servo object to control a servo 
int val;    // variable to read the value from the analog pin 
int servoAngle = 40;
int servoLeft = 90 - servoAngle;
int servoRight = 90 + servoAngle;
int servoCenter = 90;
//
int motorRight = 11;
int motorLeft = 12;

int goforward(int speed) {  
  digitalWrite(motorRight, HIGH);
  digitalWrite(motorLeft, HIGH);
}

int turnaround(int speed) {
  digitalWrite(motorRight, LOW);
  digitalWrite(motorLeft, LOW);
}

int goright(int speed) {
  digitalWrite(motorRight, HIGH);
  digitalWrite(motorLeft, LOW);
}

int goleft(int speed) {
  digitalWrite(motorRight, LOW);
  digitalWrite(motorLeft, HIGH);
}

int LockOnDistance = 16;

//Target Seeking, Mode = 0 ==============================================================================================================================================
int findtarget() {
  
  int center = readsonar();
  
  Serial.print("Center ");
  Serial.print(center);
  Serial.print(" of ");
  Serial.println(LockOnDistance);
  
  if (center < LockOnDistance) {
    goforward(255); //Go forward!
  } else {
    mode = 1;
  }
}

//Fine-Tune Targeting, Mode = 1 =======================================================================================================================================================
int lockontarget() {
    // Reading and moving the sonar
    //myservo.write(servoCenter);                  // sets the servo position according to the scaled value 
    //delay (500);
    
    int Center = readsonar(); 
    myservo.write(servoLeft);                  // sets the servo position according to the scaled value 
    delay (500);
    
    int Left = readsonar();
    myservo.write(servoRight);                  // sets the servo position according to the scaled value 
    delay (500);
    
    int Right = readsonar();
    myservo.write(servoCenter);                  // sets the servo position according to the scaled value 
    //delay (500);
    
    int cm10 = 10;
    int cm3  = 3;
    
    //Speed and Direction Control
     if ((Center < Right) && (Center < Left)) {
       // going to center
       Serial.println("center");
       if (Center > cm10) {
         goforward(255); //Go forward!
       } else if (Center > cm3)  {
         goforward(128); //
       } else {
         Serial.println("Locked center!");   
         mode = 2;
       }
     } else if ((Right < Center) && (Right < Left)) {
       // going to right
       Serial.println("right");
       if (Right > cm10) {
         goright(255); //Go forward!
       } else if (Right > cm3) {
         goright(128); //
       } else {
         mode = 2;
       }
     } else if ((Left < Center) && (Left < Right)) {
       // going to left
       Serial.println("left");
       if (Left > cm10) {
         goleft(255); //Go forward!
       } else if (Left > cm3) {
         goleft(128); //
       } else {
         mode = 2;
       }
     }
 }


// Main Program  =======================================================================================================================================================
void setup() 
{ 
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  mode = 1;
} 

void loop() {
  
  if (mode == 0) {
    
//   Serial.println("findtarget");
    findtarget();
    
  } else if (mode == 1){
    
//    Serial.println("lockontarget");
    lockontarget();
    
  } else if (mode == 2) {
    
    Serial.println("LOCKED");
    //makesomenoise();
    //turnaround(255);
//    mode = 0;

  }
//   Serial.println(mode, DEC);         // print out the average distance to the debugg 
//    Serial.println("Next loop");

  delay(1500);
  
}

