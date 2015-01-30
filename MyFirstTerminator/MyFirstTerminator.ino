#include <DRV8835MotorShield.h>

/*
 * This example uses the DRV8835MotorShield library to drive each motor with the
 * Pololu DRV8835 Dual Motor Driver Shield for Arduino forward, then backward. 
 * The yellow user LED is on when a motor is set to a positive speed and off when
 * a motor is set to a negative speed.
 */

#define LED_PIN 13
#define PROG_PIN 12
#define START_PROG 11
DRV8835MotorShield motors;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PROG_PIN, INPUT_PULLUP);
  pinMode(START_PROG, INPUT_PULLUP);
  // uncomment one or both of the following lines if your motors' directions need to be flipped
  //motors.flipM1(true);
  //motors.flipM2(true);
}


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


/* Drivetrain Turn Left full speed*/
int goleft(int speed) {  
  motors.setM1Speed(0);
  motors.setM2Speed(speed);
}


/*Drivetrain turn around*/
int turnaround(int speed) {
  
  motors.setM1Speed(-speed);
  motors.setM2Speed(speed);
  delay(3000);
  motors.setM1Speed(0);
  motors.setM2Speed(0);
}

int status_but = 0;
int cmd_num = 0;
  
void loop()
{
  if (digitalRead(PROG_PIN) == false)
  {    
    delay(200);
    while(digitalRead(PROG_PIN) == false);
    if(cmd_num < 4)
    {
      cmd_num++;
    }
    else
    {
      cmd_num = 0;
    }
    
    Serial.println(cmd_num);
    goforward(0);
  }
  
  if (digitalRead(START_PROG) == false)
  {    
    delay(200);
    while(digitalRead(START_PROG) == false);
    Serial.println("button");
    status_but  = !status_but;
    if (status_but)
    {
      switch(cmd_num)
      {
        default:
           goforward(400);
          break;    
        case 1:
           goreverse(-400);
          break;      
        case 2:
           goright(400);
          break;          
        case 3:
           goleft(400);          
          break; 
                 
        case 4:
          turnaround(400);               
          break; 
      }
    }
    else
    {
      goforward(0);
    }
    
    
    
    
    
  }
  
  
  //digitalWrite(LED_PIN, digitalRead(PROG_PIN)|digitalRead(START_PROG));
  
  // run M1 motor with positive speed
  
  /*digitalWrite(LED_PIN, HIGH);
  
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setM1Speed(speed);
    delay(2);
  }

  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setM1Speed(speed);
    delay(2);
  }
  
  // run M1 motor with negative speed
  
  digitalWrite(LED_PIN, LOW);
  
  for (int speed = 0; speed >= -400; speed--)
  {
    motors.setM1Speed(speed);
    delay(2);
  }
  
  for (int speed = -400; speed <= 0; speed++)
  {
    motors.setM1Speed(speed);
    delay(2);
  }

  // run M2 motor with positive speed
  
  digitalWrite(LED_PIN, HIGH);
  
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setM2Speed(speed);
    delay(2);
  }

  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setM2Speed(speed);
    delay(2);
  }
  
  // run M2 motor with negative speed
  
  digitalWrite(LED_PIN, LOW);
  
  for (int speed = 0; speed >= -400; speed--)
  {
    motors.setM2Speed(speed);
    delay(2);
  }
  
  for (int speed = -400; speed <= 0; speed++)
  {
    motors.setM2Speed(speed);
    delay(2);
  }
  
  delay(500);*/
}
