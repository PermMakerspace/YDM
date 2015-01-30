

int mode = 0;

#include <Ultrasonic.h>
#include <Servo.h> 
#include <DRV8835MotorShield.h>


Ultrasonic ultrasonic(4,3); // (Trig PIN,Echo PIN)

// Function for sonar reader ============================================================================================================================================================
int readsonar() {
  return ultrasonic.Ranging(CM); // CM or INC;
}

// Drivetrain vars =================================

DRV8835MotorShield motors;

int fullSpeed = 400;  //400
int lowSpeed = 150;  //150
 
// Drivetrain movement command functions =======================================================================================================================

/* Drivetrain Forward */
int goforward(int speed) {
  motors.setM1Speed(speed);
  motors.setM2Speed(speed);
}

/* Drivetrain Reverse */
int goreverse(int speed) {
  motors.setM1Speed(-1 * speed);
  motors.setM2Speed(-1 * speed);
}

/* Drivetrain Turn Right */
int goright(int speed) {
  motors.setM1Speed(speed);
  motors.setM2Speed(0);
}

/* Drivetrain Turn Left */
int goleft(int speed) {  
  motors.setM1Speed(0);
  motors.setM2Speed(speed);
}

/* Drivetrain turn around over left */
int turnaround(int speed) {
  
  motors.setM1Speed(-speed);
  motors.setM2Speed(speed);
  delay(3000);                //Time to turn
  motors.setM1Speed(0);
  motors.setM2Speed(0);
}

//Target Seeking, Mode = 0 ==============================================================================================================================================
Servo myservo;  // create servo object to control a servo 

int servoAngle = 40;
int servoLeft = 90 - servoAngle;
int servoRight = 90 + servoAngle;
int servoCenter = 90;

int LockOnDistance = 16;  //cm

int findtarget() {
  
  int center = readsonar();
  
  Serial.print("Center ");
  Serial.print(center);
  Serial.print(" of ");
  Serial.println(LockOnDistance);
  
  if (center > LockOnDistance) {
    goforward(fullSpeed); //Go forward!
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
         goforward(fullSpeed); //Go forward!
       } else if (Center > cm3)  {
         goforward(lowSpeed); //
       } else {
         Serial.println("Locked center!");   
         mode = 2;
       }
     } else if ((Right < Center) && (Right < Left)) {
       // going to right
       Serial.println("right");
       if (Right > cm10) {
         goright(fullSpeed); //Go forward!
       } else if (Right > cm3) {
         goright(lowSpeed); //
       } else {
         mode = 2;
       }
     } else if ((Left < Center) && (Left < Right)) {
       // going to left
       Serial.println("left");
       if (Left > cm10) {
         goleft(fullSpeed); //Go forward!
       } else if (Left > cm3) {
         goleft(lowSpeed); //
       } else {
         mode = 2;
       }
     }
 }


// Main Setup  =======================================================================================================================================================
void setup() 
{ 
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 

  //Motor init
  // uncomment one or both of the following lines if your motors' directions need to be flipped
  motors.flipM1(true);  //Left
  //motors.flipM2(true);  //Right

  //Neck init
  myservo.attach(5);  // attaches the servo on pin 9 to the servo object 
  
  mode = 0;
} 

// Main Loop  ===================================
void loop() {
  
  if (mode == 0) {
    
//   Serial.println("findtarget");
    findtarget();
    
  } else if (mode == 1){
    
//    Serial.println("lockontarget");
    lockontarget();
    
  } else if (mode == 2) {
    
    Serial.println("LOCKED");
    delay(10000);
    //makesomenoise();
    //turnaround(255);
//    mode = 0;

  }
//   Serial.println(mode, DEC);         // print out the average distance to the debugg 
//    Serial.println("Next loop");

  delay(1500);
  
}

