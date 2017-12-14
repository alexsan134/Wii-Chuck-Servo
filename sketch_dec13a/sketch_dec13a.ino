#include <Wiichuck.h>
#include <Wire.h>
#include <Servo.h>

Wiichuck wii;
Servo servo;
const int ServoPin = 3;


void setup() {
  Serial.begin(9600);
  servo.attach(ServoPin);
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

    if(jxServo < 0){
        jxServo = 0;
      }
    if(jxServo > 180){
        jxServo = 180;
      }
    servo.write(jxServo);
    delay(5);
  }
}
