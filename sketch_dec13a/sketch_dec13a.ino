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

void lightsLeft(int ll1, int ll2, int ll3) {
  tone(bass, 300);
  digitalWrite(ll1, HIGH);
  digitalWrite(ll2, HIGH);
  delay(300);
  noTone(bass);
  digitalWrite(ll2, LOW);
  delay(300);
}

void lightsRight(int lr1, int lr2, int lr3) {
  tone(bass, 300);
  digitalWrite(lr1, HIGH);
  digitalWrite(lr3, HIGH);
  delay(300);
  noTone(bass);
  digitalWrite(lr3, LOW);
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
/*
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
      digitalWrite(motorL, LOW);
        digitalWrite(motorR, LOW);
      if (jyServo < 150) {
        if (jxServo < 80) {
          lightsLeft(ledBack, ledBackI, ledBackD);
        } else if (jxServo > 100) {
          lightsRight(ledBack, ledBackI, ledBackD);
        }
        else if (jxServo > 10 && jxServo < 170) {
          lightsOff(ledBack);
        } else {
          lightsTurn(ledBack);
        }

      } else {
        lightsBlink(ledBack, ledBackI, ledBackD);
      }
    } else {
      lightsTurn(ledBack);
    }

    if (wii.buttonC() > 0) {
      if (jyServo < 150) {
        if (jxServo < 80) {
          lightsLeft(ledFront, ledFrontI, ledFrontD);
        } else if (jxServo > 100) {
          lightsRight(ledFront, ledFrontI, ledFrontD);
        }
        else if (jxServo > 10 && jxServo < 170) {
          lightsOff(ledFront);
        } else {
          lightsTurn(ledFront);
        }
      }
      else {
        lightsBlink(ledFront, ledFrontI, ledFrontD);
      }
    } else {
      lightsTurn(ledFront);
    }
    if(jyServo > 120){
        digitalWrite(motorL, HIGH);
        digitalWrite(motorR, LOW);
      }
      else if(jyServo < 60){
        digitalWrite(motorL, LOW);
        digitalWrite(motorR, HIGH);
      }
      else{
        digitalWrite(motorL, LOW);
        digitalWrite(motorR, LOW);
        }
    servo.write(axServo);
    delay(1);
  }
*/
  if(Serial.available() > 0){
       state = Serial.read();
  } 


 else if (state == '1') {
   lightsTurn(ledFront);
  lightsTurn(ledBack);
   digitalWrite(motorL, HIGH);
   digitalWrite(motorR, LOW);
 }
 else if (state == '2') {
    lightsOff(ledFront);
 }
 else if (state == '3') {
   lightsOff(ledFront);
    lightsTurn(ledFront);
    lightsLeft(ledFront, ledFrontI, ledFrontD);
 }
 else if (state == '4') {
   lightsOff(ledFront);
    lightsTurn(ledFront);
    lightsRight(ledFront, ledFrontI, ledFrontD);
 }
 else if (state == '5') {
      lightsOff(ledFront);
    lightsTurn(ledFront);
 }



 else if (state == '6') {
    lightsOff(ledBack);
    digitalWrite(motorL, LOW);
        digitalWrite(motorR, HIGH);
 }
 else if (state == '7') {
   lightsOff(ledBack);
    lightsTurn(ledBack);
    lightsLeft(ledBack, ledBackI, ledBackD);
 }
 else if (state == '8') {
   lightsOff(ledBack);
    lightsTurn(ledBack);
    lightsRight(ledBack, ledBackI, ledBackD);
 }
 else if (state == '9') {
      lightsOff(ledBack);
    lightsTurn(ledBack);
 }


 
delay(10);


}
