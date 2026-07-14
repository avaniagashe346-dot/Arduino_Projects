#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pin Allocations
const int SERVO_PIN = 9;
const int TRIG_PIN  = 11;
const int ECHO_PIN  = 12;

// Threshold distance in cm (If an object is closer than this, the slot is full)
const int PARKING_THRESHOLD = 10; 

LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo gateServo;

// Helper Function to calculate distance
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2; 
  return distance;
}

void setup() {
  gateServo.attach(SERVO_PIN);
  gateServo.write(0); // Start with gate closed
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  lcd.init();
  lcd.backlight();
}

void loop() {
  long distance = getDistance();

  // If distance is valid and less than threshold -> Car is Parked/Detected
  if (distance > 0 && distance <= PARKING_THRESHOLD) {
    gateServo.write(90); // Open the gate
    lcd.setCursor(0, 0);
    lcd.print("Slot: OCCUPIED  ");
    lcd.setCursor(0, 1);
    lcd.print("Gate: OPEN      ");
    
    delay(2000);  
        // <-- NEW: Pauses everything here for 3 seconds while gate stays open
  } 
  // Otherwise -> Slot is empty
  else {
    gateServo.write(0); // Close the gate
    lcd.setCursor(0, 0);
    lcd.print("Slot: EMPTY     ");
    lcd.setCursor(0, 1);
    lcd.print("Gate: CLOSED    ");
  }

  delay(200); // 0.2 second delay to keep data stable on the screen
}