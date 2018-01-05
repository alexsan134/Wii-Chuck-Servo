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
char h;
int ia = 0;

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
  digitalWrite(ledBack, LOW);
  digitalWrite(ledFront, LOW);
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

void acelerate() {
  lightsTurn(ledBack);
  digitalWrite(motorL, HIGH);
  digitalWrite(motorR, LOW);
}
void reverse() {
  lightsOff(ledBack);
  lightsTurn(ledFront);
  digitalWrite(motorL, LOW);
  digitalWrite(motorR, HIGH);
}
void stopIt() {
  lightsTurn(ledBack);
  lightsTurn(ledFront);
  digitalWrite(motorL, LOW);
  digitalWrite(motorR, LOW);
}


void loop() {
  if (Serial.available() > 0) {
    state = Serial.read();
  }

  if (digitalRead(changeUp) == HIGH) {

    if (wii.poll()) {
      int jxServo = wii.joyX() - 42;
      int jyServo = wii.joyY() - 42;
      int axServo = (wii.accelY() / 2) - 157;
      int ayServo = (wii.accelX() / 2) - 187;

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

      if (jyServo > 120) {
        if (wii.buttonZ() > 0) {
          reverse();
        } else {
          acelerate();
        }
      } else {
        if (wii.buttonZ() > 0) {
          reverse();
        }
        else {
          stopIt();
        }
      }

      if (wii.buttonC() > 0) {
        lightsOff(ledFront);
        lightsTurn(ledBack);
        if (jxServo < 60) {
          lightsLeft();
        }
        else if (jxServo > 120) {
          lightsRight();
        }
        else if (jxServo > 60 &&  jxServo < 120) {
          lightsOff(ledFront);
        }
      }
      servo.write(axServo);
    }
  } else {
    if (state == 'b') {
      lightsOff(ledFront);
    }
    else if (state == 'c') {
      reverse();
      servo.write(ia * 13);
    }
    else if (state == 'd') {
      stopIt();
    }
    else if (state == 'e') {
      lightsLeft();
    }
    else if (state == 'f') {
      lightsRight();
    } else {
      h = state;
      ia = h - '0';

      if (h > 110) {
        h = 110;
      }
      if (h < 60) {
        h = 60;
      }
      if (digitalRead(ledBack) == HIGH) {
        reverse();
      } else {
        acelerate();
      }
      servo.write(ia * 13);
    }


    delay(10);
  }

}
