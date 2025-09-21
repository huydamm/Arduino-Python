int pinA = 4, pinB = 2, pinC = 6, pinD = 8;
int pinE = 9, pinF = 3, pinG = 5, pinDP = 7;
int D1 = 10, D2 = 11, D3 = 12, D4 = 13;

String inputString = "0000";

void setup() {
  Serial.begin(9600);

  pinMode(pinA, OUTPUT); pinMode(pinB, OUTPUT); pinMode(pinC, OUTPUT); pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT); pinMode(pinF, OUTPUT); pinMode(pinG, OUTPUT); pinMode(pinDP, OUTPUT);
  pinMode(D1, OUTPUT); pinMode(D2, OUTPUT); pinMode(D3, OUTPUT); pinMode(D4, OUTPUT);

  clearDisplay();
}

void loop() {
  // Read serial if available
  if (Serial.available()) {
    inputString = Serial.readStringUntil('\n');
    inputString.trim();  // remove newline or spaces
    if (inputString.length() < 4) {
      inputString = String("0000" + inputString).substring(inputString.length());
    }
  }

  displayNumber(inputString);
}

void displayNumber(String number) {
  for (int i = 0; i < 4; i++) {
    activateDigit(i);
    displayDigit(number.charAt(i));
    delay(2);
    clearDisplay();
  }
}

// Display one digit
void displayDigit(char ch) {
  bool segments[7] = {0};
  switch (ch) {
    case '0': segments[0]=1;segments[1]=1;segments[2]=1;segments[3]=1;segments[4]=1;segments[5]=1; break;
    case '1': segments[1]=1;segments[2]=1; break;
    case '2': segments[0]=1;segments[1]=1;segments[6]=1;segments[4]=1;segments[3]=1; break;
    case '3': segments[0]=1;segments[1]=1;segments[2]=1;segments[3]=1;segments[6]=1; break;
    case '4': segments[1]=1;segments[2]=1;segments[5]=1;segments[6]=1; break;
    case '5': segments[0]=1;segments[2]=1;segments[3]=1;segments[5]=1;segments[6]=1; break;
    case '6': segments[0]=1;segments[2]=1;segments[3]=1;segments[4]=1;segments[5]=1;segments[6]=1; break;
    case '7': segments[0]=1;segments[1]=1;segments[2]=1; break;
    case '8': segments[0]=1;segments[1]=1;segments[2]=1;segments[3]=1;segments[4]=1;segments[5]=1;segments[6]=1; break;
    case '9': segments[0]=1;segments[1]=1;segments[2]=1;segments[3]=1;segments[5]=1;segments[6]=1; break;
  }
  digitalWrite(pinA, segments[0]);
  digitalWrite(pinB, segments[1]);
  digitalWrite(pinC, segments[2]);
  digitalWrite(pinD, segments[3]);
  digitalWrite(pinE, segments[4]);
  digitalWrite(pinF, segments[5]);
  digitalWrite(pinG, segments[6]);
}

void activateDigit(int digit) {
  digitalWrite(D1, digit != 0);
  digitalWrite(D2, digit != 1);
  digitalWrite(D3, digit != 2);
  digitalWrite(D4, digit != 3);
}

void clearDisplay() {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}

