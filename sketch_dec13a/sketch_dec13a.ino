#include <Wiichuck.h>
#include <Wire.h>
#include <Servo.h>

Wiichuck wii;
Servo servo;
Servo servoY;
const int motorL = 2;
const int motorR = 3;
const int ServoPin = 4;
const int ledBack = 5;
const int ledBackI = 6;
const int ledBackD = 7;
const int ledFront = 8;
const int ledFrontI = 9;
const int ledFrontD = 10;
const int bass = 11;
const int changeUp = 12;
int state = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(ServoPin);
  pinMode(ledBack, OUTPUT);
  pinMode(changeUp, INPUT);
  pinMode(ledBackI, OUTPUT);
  pinMode(ledBackD, OUTPUT);
  pinMode(ledFront, OUTPUT);
  pinMode(ledFrontI, OUTPUT);
  pinMode(ledFrontD, OUTPUT);
  pinMode(motorL, OUTPUT);
  pinMode(motorR, OUTPUT);
  pinMode(bass, OUTPUT);
  pinMode(13, OUTPUT);
  wii.init();
  wii.calibrate();
  digitalWrite(ledBack, HIGH);
  digitalWrite(ledFront, HIGH);
  digitalWrite(13, LOW);
  delay(200);
  tone(bass, 800);
  delay(80);
  tone(bass, 1000);
  delay(200);
  noTone(bass);
  delay(3000);
  digitalWrite(changeUp, HIGH);
    digitalWrite(ledBack, LOW);
  digitalWrite(ledFront, LOW);
}

void lightsBlink(int l1, int l2, int l3) {
  tone(bass, 100);
  digitalWrite(l1, LOW);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, HIGH);
  delay(100);
  noTone(bass);
  digitalWrite(l2, LOW);
  digitalWrite(l3, LOW);
  delay(100);
}

void lightsLeft() {
  tone(bass, 300);
  digitalWrite(ledBackI, HIGH);
  digitalWrite(ledFrontI, HIGH);
  delay(300);
  noTone(bass);
  digitalWrite(ledFrontI, LOW);
  digitalWrite(ledBackI, LOW);
  delay(300);
}

void lightsRight() {
  tone(bass, 300);
  digitalWrite(ledBackD, HIGH);
  digitalWrite(ledFrontD, HIGH);
  delay(300);
  noTone(bass);
  digitalWrite(ledBackD, LOW);
  digitalWrite(ledFrontD, LOW);
  delay(300);
}
void lightsOff(int e) {
  digitalWrite(ledBackD, LOW);
  digitalWrite(ledBackI, LOW);
  digitalWrite(ledFrontD, LOW);
  digitalWrite(ledFrontI, LOW);
  digitalWrite(e, HIGH);
}
void lightsTurn(int es) {
  digitalWrite(ledBackD, LOW);
  digitalWrite(ledBackI, LOW);
  digitalWrite(ledFrontD, LOW);
  digitalWrite(ledFrontI, LOW);
  digitalWrite(es, LOW);
}

void loop() {
    if(Serial.available() > 0){
       state = Serial.read();
  } 
  if(digitalRead(changeUp) == HIGH){

  if (wii.poll()) {
    int joyX = wii.joyX();
    int joyY = wii.joyY();
    int accelY = wii.accelY();
    int accelX = wii.accelX();
    int accelZ = wii.accelZ();
    int jxServo = joyX - 42;
    int jyServo = joyY - 42;
    int axServo = (accelX / 2) - 157;
    int ayServo = (accelY / 2) - 187;
    if (jxServo < 0) {
      jxServo = 0;
    }
    if (jxServo > 180) {
      jxServo = 180;
    }
    if (jyServo < 0) {
      jyServo = 0;
    }
    if (jyServo > 180) {
      jyServo = 180;
    }

    if (axServo < 60) {
      axServo = 60;
    }
    if (axServo > 110) {
      axServo = 110;
    }
    if (ayServo < 0) {
      ayServo = 0;
    }
    if (ayServo > 180) {
      ayServo = 180;
    }

    if (wii.buttonZ() > 0) {
      lightsOff(ledBack);
    lightsTurn(ledFront);
    digitalWrite(motorL, LOW);
   digitalWrite(motorR, HIGH);
   if(jxServo < 60){
        lightsLeft();
    }
    else if (jxServo > 120){
        lightsRight();
      }
      else if(jxServo > 60 &&  jxServo < 120){
          lightsOff(ledBack);
        }
    } else {
      lightsTurn(ledBack);
      digitalWrite(motorL, LOW);
   digitalWrite(motorR, LOW);
    }
    

    if (wii.buttonC() > 0) {
       lightsOff(ledFront);
    lightsTurn(ledBack);
   if(jxServo < 60){
        lightsLeft();
    }
    else if (jxServo > 120){
        lightsRight();
      }
      else if(jxServo > 60 &&  jxServo < 120){
          lightsOff(ledFront);
        }
    } else {
      lightsTurn(ledFront);
      digitalWrite(motorL, LOW);
   digitalWrite(motorR, LOW);
    }
    servo.write(axServo);
  }
  }else{


 if (state == '1') {
   lightsTurn(ledFront);
  lightsTurn(ledBack);
   digitalWrite(motorL, HIGH);
   digitalWrite(motorR, LOW);
 }
 else if (state == '2') {
    lightsOff(ledFront);
 }

 else if (state == '3') {
    lightsTurn(ledBack);
    lightsTurn(ledFront);
    digitalWrite(motorL, LOW);
   digitalWrite(motorR, LOW);
 }
 
 else if (state == '4') { 
   lightsOff(ledBack);
    lightsTurn(ledFront);
    digitalWrite(motorL, LOW);
   digitalWrite(motorR, HIGH);
 }
 else if (state == '5') {
    lightsTurn(ledBack);
    lightsTurn(ledFront);
    digitalWrite(motorL, LOW);
   digitalWrite(motorR, LOW);
 }



 else if (state == '6') {
    lightsLeft();
 }
 else if (state == '7') {
lightsRight();
 }

delay(10);
  }

}
