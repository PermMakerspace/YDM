//This file contains original Setup and Loop for production
// Main Setup  =======================================================================================================================================================
void setup() 
{ 
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 

  //Motor init
  // uncomment one or both of the following lines if your motors' directions need to be flipped
  //motors.flipM1(true);
  //motors.flipM2(true);

  //Neck init
  myservo.attach(5);  // attaches the servo on pin 9 to the servo object 
  
  mode = 1;
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
    //makesomenoise();
    //turnaround(255);
//    mode = 0;

  }
//   Serial.println(mode, DEC);         // print out the average distance to the debugg 
//    Serial.println("Next loop");

  delay(1500);
  
}

