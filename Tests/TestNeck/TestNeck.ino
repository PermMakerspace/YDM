//This test replaces Setup and Loop procedures for testing purpose
void loop() {

  Serial.println("lockontarget()");
  myservo.write(servoLeft);                  // sets the servo position according to the scaled value 
  delay (500);
  myservo.write(servoRight);                  // sets the servo position according to the scaled value 
  delay (500);
  myservo.write(servoCenter);                  // sets the servo position according to the scaled value 
  //delay (500);

  delay(1000);

}

