#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define trigPin 4
#define echoPin 3



void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(4,0);;
  lcd.print("Ultrasonic Dist");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("Target distance: ");
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH,30000);
  distance = (duration/2) / 29.1;

  lcd.setCursor(0,1);
  lcd.print("       ");
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.print(" cm");
  delay(250);


}
