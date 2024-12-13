#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPins[29] = {3, 5, 7, 9, 11, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, A0, A2, A4, A6, A8, A10, A12, A14};
const int echoPins[29] = {4, 6, 8, 10, 12, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, A1, A3, A5, A7, A9, A11, A13, A15};

long startTimes[29];
int distance[29];
int occupied = 0;
int available = 29;

void setup() {
  lcd.init();
  lcd.backlight();

  for (int i = 0; i < 29; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
    digitalWrite(trigPins[i], LOW);
  }

  Serial.begin(115200);
}

void loop() {
  occupied = 0;
  available = 29;

  for (int i = 0; i < 29; i++) {
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);

    long duration = pulseIn(echoPins[i], HIGH, 30000);
    if (duration > 0) {
      distance[i] = duration * 0.034 / 2;
    } else {
      distance[i] = -1;
    }

    if (distance[i] < 5 || distance[i] > 800) {
      occupied++;
      available--;
    }

    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    if (distance[i] != -1) {
      Serial.print(distance[i]);
      Serial.println(" cm");
    } else {
      Serial.println("N/A");
    }

    delay(100);
  }

  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("P ocupate");
  lcd.print(available);

  lcd.setCursor(0, 1);
  lcd.print("P disponibile:");
  lcd.print(occupied);

  delay(500);
}
