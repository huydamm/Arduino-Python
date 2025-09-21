#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define vibOutPin 3
#define btnA 5
#define btnB 6
#define btnC 7

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Correct answer
char correctAnswer = 'B';

void setup() {
  pinMode(vibOutPin, OUTPUT);
  pinMode(btnA, INPUT_PULLUP);
  pinMode(btnB, INPUT_PULLUP);
  pinMode(btnC, INPUT_PULLUP);
  
  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);
  showQuestion();
}

void loop() {
  if (digitalRead(btnA) == LOW) {
    checkAnswer('A');
    delay(1000);
  } else if (digitalRead(btnB) == LOW) {
    checkAnswer('B');
    delay(1000);
  } else if (digitalRead(btnC) == LOW) {
    checkAnswer('C');
    delay(1000);
  }
}

void showQuestion() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Q: 2 + 2 = ?");
  lcd.setCursor(0, 1);
  lcd.print("A)3 B)4 C)5");
}

void checkAnswer(char userAnswer) {
  lcd.clear();
  if (userAnswer == correctAnswer) {
    lcd.setCursor(0, 0);
    lcd.print("Correct!");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Wrong Answer!");
    vibrate();
  }
  
  delay(2000);
  showQuestion();
}

void vibrate() {
  digitalWrite(vibOutPin, HIGH);
  delay(300);
  digitalWrite(vibOutPin, LOW);
  delay(200);
  digitalWrite(vibOutPin, HIGH);
  delay(300);
  digitalWrite(vibOutPin, LOW);
}

