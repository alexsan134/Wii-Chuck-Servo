#include <Wiichuck.h>
#include <Wire.h>
#include <Servo.h>

Wiichuck wii;
Servo servo;
Servo servoY;
const int ServoPin = 3;
const int ServoPinY = 4;
const int ledZ = 5;


void setup() {
  Serial.begin(9600);
  servo.attach(ServoPin);
  servoY.attach(ServoPinY);
  pinMode(ledZ, OUTPUT);
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
          digitalWrite(ledZ, HIGH);
      }else{
        digitalWrite(ledZ, LOW);
        }
    servo.write(axServo);
    servoY.write(ayServo);
    delay(1);
  }
}
