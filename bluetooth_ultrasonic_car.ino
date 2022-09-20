#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
int rm1 = 2;
int rm2 = 3;
int lm1 = 4;
int lm2 = 5;
int trig = 11, echo = 12, buzzer = 13;
char reading = 'm';
int distance = 0;
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.println("distance : ");
  Serial.begin(9600);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  ultrasonic();
  Serial.print(reading);
  Serial.println(distance);
  lcd.println(distance);
  lcd.setCursor(12, 0);
  if (Serial.available() > 0) {
    reading = Serial.read();
    switch (reading) {
      case 'F' : {
          forward();
          break;
        }
      case 'B' : {
          backward();
          break;
        }
      case 'R' : {
          right();
          break;
        }
      case 'L' : {
          left();
          break;
        }
      case 'S' : {
          Stop();
          break;
        }
      case 'U' : {
          while (1) {
            reading = Serial.read();
            ultrasonic();
            ultrasonic_v2();
            lcd.println(distance);
            lcd.setCursor(12, 0);
            if (reading == 'F' || reading == 'B' || reading == 'R' || reading == 'L') {
              break;
            }
          }
          break;
        }
    }
  }
}
void left() {
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}
void right() {
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}
void backward() {
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}
void forward() {
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}
void ultrasonic_forward() {
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}
void ultrasonic_right() {
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}
void Stop() {
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);
}
void ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(20);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  distance = duration * 0.0344;

}
void ultrasonic_v2() {
  if (distance > 25) {
    forward();
    Serial.println('F');
  }
  else {
    Stop();
    Serial.println('S');
    tone(buzzer, 4000);
    delay(250);
    right();
    Serial.println('R');
    delay(250);
    noTone(13);
  }
}
