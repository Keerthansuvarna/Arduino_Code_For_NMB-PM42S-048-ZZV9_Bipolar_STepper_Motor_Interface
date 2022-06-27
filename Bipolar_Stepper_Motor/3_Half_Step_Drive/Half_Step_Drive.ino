#include<Arduino.h>
#include<stdio.h>
#include<math.h>

/*_________________________________________________________________________________________________

   ######################## Bipolar Stepper Motor Drive - NMB PM42S-048 #####################
   #################################### NMB PM42S-048-ZZV9 ##################################

  NMB PM42S-048 Series Stepper motors are the universal stepper motor. Which can be used as both
  UNIPOLAR & BIPOLAR.IT Comes with 6 wire in which 2 wires are centre tapped.
  The Stepper motor will rotate with a step angle of 7.5 Degree if we use Full Step wave drive.

  Wiring Connection:
  ------------------------------------------------------
  ARDUINO         |  L298N Driver  |     NMB PM42S-048 |
  ------------------------------------------------------
     8            |      IN1       |     No Connection |
     9            |      IN2       |     No Connection |
    10            |      IN3       |     No Connection |
    11            |      IN4       |     No Connection |
  ------------------------------------------------------
  No Connection   |      OUT1      |     Black  - Wire |
  No Connection   |      OUT2      |     Brown  - Wire |
  No Connection   |      OUT3      |     Yellow - Wire |
  No Connection   |      OUT4      |     Orange - Wire |
  ------------------------------------------------------
  No Connection   |      Nill      |     RED - Wire    |
  No Connection   |      Nill      |     RED - Wire    |
  ------------------------------------------------------
  No Connection   |5V DC (Not Used)|        Nill       |
  No Connection   |   12V DC (Vin) |        Nill       |
  No Connection   |       GND      |        Nill       |
  ------------------------------------------------------
  Note: If you want to run the motor in UNIPOLAR configuration then
        connect the both RED wire to +12V Power Supply.

  #################################### Calculations ##################################

  1 step = 3.75 Degree i.e, 360/3.75 = 96 steps per rotation

  ########################### Two Phase Full Step Drive ###########################

                  Half Step Drive
  -----------------------------------------------------------
  Total |   Black   |    Orange  |    Brown  |   Yellow   |
  Steps |    IN1    |      IN3   |     IN2   |    IN4     |
  -----------------------------------------------------------
    1   |    1      |       0    |      0    |    0       |
    2   |    1      |       1    |      0    |    0       |
    3   |    0      |       1    |      0    |    0       |
    4   |    0      |       1    |      1    |    0       |
    5   |    0      |       0    |      1    |    0       |
    6   |    0      |       0    |      1    |    1       |  
    7   |    0      |       0    |      0    |    1       |
    8   |    1      |       0    |      0    |    1       |              
  -----------------------------------------------------------
                         Tested with Arduino Uo
  __________________________________________________________________________________________________ */

/* Define the Arduino Pins to control driver */

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

/* Variables to count total steps & rotations */
int i;
int step_count = 0;
int rotation_count = 0;

/* Variables to change the direction */
bool cw = true;
bool ccw = false;

/* Variables to change the speed - RPM */
int set_speed = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

}

void loop()
{
  if (cw)
  {
    for (i = 1; i <= 8; i++)
    {
      switch (i)
      {
        case 1:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
        case 2:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count++;
          delay(100);
          break;
        case 3:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count++;
          delay(100);
          break;
        case 4:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count++;
          delay(100);
          break;
          case 5:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
          case 6:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
          case 7:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
          case 8:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
      }

      if (step_count % 96 == 0)
      {
        rotation_count++;
        Serial.print(" Total Rotations Completed : ");
        Serial.println(rotation_count);
        delay(2000);
        step_count = 0;
        cw = false;
        ccw = true;
        break;
      }
    }
    if (i == 8)
      i = 1;

  }

  else if (ccw)
  {
    for (i = 8; i >= 1; i--)
    {
      switch (i)
      {
        case 1:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
        case 2:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count++;
          delay(100);
          break;
        case 3:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count++;
          delay(100);
          break;
        case 4:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count++;
          delay(100);
          break;
          case 5:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
          case 6:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
          case 7:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
          case 8:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
      }
      if (step_count % 98 == 0)
      {
        rotation_count++;
        Serial.print(" Total Rotations Completed : ");
        Serial.println(rotation_count);
        delay(2000);
        step_count = 0;
        cw = true;
        ccw = false;
        break;
      }
    }
    if (i == 1)
      i = 8;

  }

  else
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

  }

}
