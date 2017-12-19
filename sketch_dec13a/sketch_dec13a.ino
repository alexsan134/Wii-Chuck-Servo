#include <Wiichuck.h>
#include <Wire.h>
#include <Servo.h>

Wiichuck wii;
Servo servo;
Servo servoY;
const int ServoPin = 3;
const int ServoPinY = 4;
const int ledBack = 5;
const int ledBackI = 6;
const int ledBackD = 7;
const int ledFront = 8;
const int ledFrontI = 9;
const int ledFrontD = 10;


void setup() {
  Serial.begin(9600);
  servo.attach(ServoPin);
  servoY.attach(ServoPinY);
  pinMode(ledBack, OUTPUT);
  pinMode(ledBackI, OUTPUT);
  pinMode(ledBackD, OUTPUT);
  pinMode(ledFront, OUTPUT);
  pinMode(ledFrontI, OUTPUT);
  pinMode(ledFrontD, OUTPUT);
  wii.init();
  wii.calibrate();
}

void loop() {
  if (wii.poll()) {
    int joyX = wii.joyX();
    int joyY = wii.joyY();
    int accelY = wii.accelY();
    int accelX = wii.accelX();
    int accelZ = wii.accelZ();
    int jxServo = joyX - 42;
    int jyServo = joyY - 42;
    int axServo = (accelX/2)-157;
    int ayServo = (accelY/2)-187;

    if(jxServo < 0){
        jxServo = 0;
      }
    if(jxServo > 180){
        jxServo = 180;
      }
       if(jyServo < 0){
        jyServo = 0;
      }
    if(jyServo > 180){
        jyServo = 180;
      }

       if(axServo < 0){
        axServo = 0;
      }
    if(axServo > 180){
        axServo = 180;
      }
       if(ayServo < 0){
        ayServo = 0;
      }
    if(ayServo > 180){
        ayServo = 180;
      }
    if(wii.buttonZ() > 0){
          if(jxServo < 80){
              digitalWrite(ledBack, HIGH);
              digitalWrite(ledBackI, HIGH);
              delay(300);
              digitalWrite(ledBackI, LOW);
              delay(300);
            }else if(jxServo > 100){
              digitalWrite(ledBack, HIGH);
              digitalWrite(ledBackD, HIGH);
              delay(300);
              digitalWrite(ledBackD, LOW);
              delay(300);
              }
               else if(jxServo > 80 && jxServo < 100){
                digitalWrite(ledBackD, LOW);
                digitalWrite(ledBackI, LOW);
                digitalWrite(ledBack, HIGH);
               }else{
                digitalWrite(ledBack, LOW);
               digitalWrite(ledBackI, LOW);
         digitalWrite(ledBackD, LOW);
                }
      }else{
        digitalWrite(ledBack, LOW);
         digitalWrite(ledBackI, LOW);
         digitalWrite(ledBackD, LOW);
        }

         if(wii.buttonC() > 0){
          if(jxServo < 80){
              digitalWrite(ledFront, HIGH);
              digitalWrite(ledFrontI, HIGH);
              delay(300);
              digitalWrite(ledFrontI, LOW);
              delay(300);
            }else if(jxServo > 100){
              digitalWrite(ledFront, HIGH);
              digitalWrite(ledFrontD, HIGH);
              delay(300);
              digitalWrite(ledFrontD, LOW);
              delay(300);
              }
               else if(jxServo > 80 && jxServo < 100){
                digitalWrite(ledFrontD, LOW);
                digitalWrite(ledFrontI, LOW);
                digitalWrite(ledFront, HIGH);
               }else{
                digitalWrite(ledFront, LOW);
               digitalWrite(ledFrontI, LOW);
         digitalWrite(ledFrontD, LOW);
                }
      }else{
        digitalWrite(ledFront, LOW);
         digitalWrite(ledFrontI, LOW);
         digitalWrite(ledFrontD, LOW);
        }
      
    servo.write(jxServo);
    delay(1);
  }
}
