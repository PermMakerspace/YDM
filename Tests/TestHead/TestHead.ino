//This test replaces Setup and Loop procedures for testing purpose
void loop() {

  Serial.println("readsonar()");
  int center = readsonar();

  Serial.print("Center ");
  Serial.print(center);
  Serial.print(" of ");
  Serial.println(LockOnDistance);

  delay(1000);

}

