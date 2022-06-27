#include <Arduino.h>
#include <stdio.h>
#include <math.h>

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

  1 step = 7.5 Degree i.e, 360/7.5 = 48 steps per rotation

  ########################### Single Phase Full Step Drive ###########################
  
                         Wave Drive
-----------------------------------------------------------
  Total |   Black   |    Orange  |    Brown  |   Yellow   |
  Steps |    IN1    |      IN4   |     IN2   |    IN3     |
-----------------------------------------------------------
    1   |    1      |       0    |      0    |    0       |
    2   |    0      |       1    |      0    |    0       |
    3   |    0      |       0    |      1    |    0       |
    4   |    0      |       0    |      0    |    1       |
-----------------------------------------------------------   
                         Tested with Arduino Uno
  __________________________________________________________________________________________________ */

/* Define the Arduino Pins to control driver */

#define IN1 8   //IN1 ---> BLACK
#define IN2 9   //IN2 ---> BROWN
#define IN3 10  //IN3 ---> YELLOW
#define IN4 11  //IN4 ---> ORANGE

/* Variables to count total steps & rotations */
int i = 0;
int step_count = 0;
int rotation_count = 0;

/* Variables to change the direction */
bool cw = true;
bool ccw = false;

/* Variables to change the speed - RPM */
int set_speed = 0;

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  /* Setting Home Position */
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  if (cw) {
    for (i = 1; i <= 4; i++) {
      switch (i) {
        case 1:

          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
        case 2:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count++;
          delay(100);
          break;
        case 3:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
        case 4:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
      }

      if (step_count % 48 == 0) {
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
    if (i == 4)
      i = 1;

  }

  else if (ccw) {
    for (i = 4; i >= 1; i--) {
      switch (i) {
        case 1:

          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
        case 2:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count++;
          delay(100);
          break;
        case 3:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
        case 4:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count++;
          delay(100);
          break;
      }
      if (step_count % 49 == 0) {
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
      i = 4;

  }

  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}