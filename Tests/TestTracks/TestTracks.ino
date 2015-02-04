//This test replaces Setup and Loop procedures for testing purpose
void loop() {

  Serial.println("goforward()");
  goforward(400);
  delay(1000);
  Serial.println("goreverse()");
  goreverse(400);
  delay(1000);
  Serial.println("goleft()");
  goleft(400);          
  delay(1000);
  Serial.println("goright()");
  goright(400);
  delay(1000);
  Serial.println("turnaround()");
  turnaround(400);               
  delay(1000);
  Serial.println("Stop");
  goforward(0);

  delay(2000);

}


