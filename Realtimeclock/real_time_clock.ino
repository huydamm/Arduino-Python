#include <LedControl.h>

// Pin configuration
const int DIN_PIN = 11;
const int CLK_PIN = 13;
const int CS_PIN = 10;
const int NUM_DISPLAYS = 1;

// Digit positions (now using all 8 digits with gaps)
const int H1_POS = 7;  // First hour digit
const int H2_POS = 6;  // Second hour digit
const int GAP1_POS = 5; // Blank gap
const int M1_POS = 4;  // First minute digit
const int M2_POS = 3;  // Second minute digit
const int GAP2_POS = 2; // Blank gap
const int S1_POS = 1;  // First second digit
const int S2_POS = 0;  // Second second digit

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, NUM_DISPLAYS);

String timeStr = "";
String lastValidTime = "000000";
unsigned long lastUpdate = 0;
unsigned long lastSerialCheck = 0;

void setup() {
  Serial.begin(115200);  // Increased baud rate
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  
  // Display initialization pattern
  for (int i = 0; i < 8; i++) {
    lc.setChar(0, i, '-', false);
    delay(70);
  }
  lc.clearDisplay(0);
}

void loop() {
  // Check for serial data more frequently
  if (millis() - lastSerialCheck > 100) {
    readSerial();
    lastSerialCheck = millis();
  }

  // Update display every second
  if (millis() - lastUpdate >= 1000) {
    if (lastValidTime.length() == 6) {
      // Increment seconds manually if no new data received
      incrementTime();
    }
    displayTime(lastValidTime);
    lastUpdate = millis();
  }
}

void readSerial() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      if (timeStr.length() == 6) {
        lastValidTime = timeStr;
        lastUpdate = millis();
      }
      timeStr = "";
    } else if (isDigit(c)) {
      timeStr += c;
    }
  }
}

void incrementTime() {
  // Convert to integer
  int hours = lastValidTime.substring(0, 2).toInt();
  int minutes = lastValidTime.substring(2, 4).toInt();
  int seconds = lastValidTime.substring(4, 6).toInt();
  
  // Increment time
  seconds++;
  if (seconds >= 60) {
    seconds = 0;
    minutes++;
    if (minutes >= 60) {
      minutes = 0;
      hours++;
      if (hours >= 24) {
        hours = 0;
      }
    }
  }
  
  // Format back to string
  char buf[7];
  snprintf(buf, sizeof(buf), "%02d%02d%02d", hours, minutes, seconds);
  lastValidTime = String(buf);
}

void displayTime(String t) {
  lc.setDigit(0, H1_POS, t.charAt(0) - '0', false);
  lc.setDigit(0, H2_POS, t.charAt(1) - '0', false);
  lc.setChar(0, GAP1_POS, ' ', false);  // Blank gap
  lc.setDigit(0, M1_POS, t.charAt(2) - '0', false);
  lc.setDigit(0, M2_POS, t.charAt(3) - '0', false);
  lc.setChar(0, GAP2_POS, ' ', false);  // Blank gap
  lc.setDigit(0, S1_POS, t.charAt(4) - '0', false);
  lc.setDigit(0, S2_POS, t.charAt(5) - '0', false);
}



