#include <Wiichuck.h>
#include <Wire.h>
#include <Servo.h>

Wiichuck wii;
Servo servo;
Servo servoY;
const int ServoPin = 4;
const int ledBack = 5;
const int ledBackI = 6;
const int ledBackD = 7;
const int ledFront = 8;
const int ledFrontI = 9;
const int ledFrontD = 10;
const int bass = 11;


void setup() {
  Serial.begin(9600);
  servo.attach(ServoPin);
  pinMode(ledBack, OUTPUT);
  pinMode(ledBackI, OUTPUT);
  pinMode(ledBackD, OUTPUT);
  pinMode(ledFront, OUTPUT);
  pinMode(ledFrontI, OUTPUT);
  pinMode(ledFrontD, OUTPUT);
  pinMode(bass, OUTPUT);
  wii.init();
  wii.calibrate();
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
    servo.write(axServo);
    delay(1);
  }
}
