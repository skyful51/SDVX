#include <RotaryEncoder.h>
#include <Keyboard.h>

// Arduino Lenoardo Wiring
#define VOL_R_DT      0
#define VOL_R_CLK     1
#define VOL_L_DT      2
#define VOL_L_CLK     3
#define BTA           4
#define BTB           5
#define BTC           6
#define BTD           7
#define BTA_LED       A0
#define BTB_LED       A1
#define BTC_LED       A2
#define BTD_LED       A3

#define ENCODER_TIME  100

// Define VOL-R, VOL-L rotary encoder
RotaryEncoder VolR(VOL_R_DT, VOL_R_CLK, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder VolL(VOL_L_DT, VOL_L_CLK, RotaryEncoder::LatchMode::TWO03);
bool isRotateVolR = false;
bool isRotateVolL = false;
unsigned long startTimeVolR = 0;
unsigned long startTimeVolL = 0;
int posVolR = 0;
int posVolL = 0;

void setup() {
  // Enable Keyboard library
  Keyboard.begin();
  pinMode(BTA, INPUT_PULLUP);
  pinMode(BTB, INPUT_PULLUP);
  pinMode(BTC, INPUT_PULLUP);
  pinMode(BTD, INPUT_PULLUP);
  pinMode(BTA_LED, OUTPUT);
  pinMode(BTB_LED, OUTPUT);
  pinMode(BTC_LED, OUTPUT);
  pinMode(BTD_LED, OUTPUT);
}

void loop() {
  //functionVolR();
  //functionVolL();
  
  if (digitalRead(BTA) == LOW) {
    Keyboard.press('d');
    digitalWrite(BTA_LED, HIGH);
  }
  else if (digitalRead(BTA) == HIGH) {
    Keyboard.release('d');
    digitalWrite(BTA_LED, LOW);
  }

  if (digitalRead(BTB) == LOW) {
    Keyboard.press('f');
    digitalWrite(BTB_LED, HIGH);
  }
  else if (digitalRead(BTB) == HIGH) {
    Keyboard.release('f');
    digitalWrite(BTB_LED, LOW);
  }
  
  if (digitalRead(BTC) == LOW) {
    Keyboard.press('j');
    digitalWrite(BTC_LED, HIGH);
  }
  else if (digitalRead(BTC) == HIGH) {
    Keyboard.release('j');
    digitalWrite(BTC_LED, LOW);
  }
  
  if (digitalRead(BTD) == LOW) {
    Keyboard.press('k');
    digitalWrite(BTD_LED, HIGH);
  }
  else if (digitalRead(BTD) == HIGH) {
    Keyboard.release('k');
    digitalWrite(BTD_LED, LOW);
  }
}

void functionVolR() {
  VolR.tick();
  int newPos = VolR.getPosition();

  // 시계 방향으로 돌아갔다
  if ((newPos - posVolR) > 0) {
    // Serial.print("Position increased: ");
    // Serial.println(newPos);
    Keyboard.release('3');
    Keyboard.press('4');
    isRotateVolR = true;
    startTimeVolR = millis();
  }
  // 시계 반대 방향으로 돌아갔다
  else if ((newPos - posVolR) < 0) {
    // Serial.print("Position decreased: ");
    // Serial.println(newPos);
    Keyboard.release('4');
    Keyboard.press('3');
    isRotateVolR = true;
    startTimeVolR = millis();
  }
  // 돌아가지 않았다
  else {
    unsigned long interTime = millis();
    if ((interTime - startTimeVolR > ENCODER_TIME) && (isRotateVolR == true)) {
      isRotateVolR = false;
      // Serial.println("Encoder stopped rotating");
      // 키보드 입력 해제 코드
      Keyboard.release('3');
      Keyboard.release('4');
    }
  }
  
  posVolR = newPos;
}

void functionVolL() {
  VolL.tick();
  int newPos = VolL.getPosition();

  // 시계 방향으로 돌아갔다
  if ((newPos - posVolL) > 0) {
    // Serial.print("Position increased: ");
    // Serial.println(newPos);
    Keyboard.release('1');
    Keyboard.press('2');
    isRotateVolL = true;
    startTimeVolL = millis();
  }
  // 시계 반대 방향으로 돌아갔다
  else if ((newPos - posVolL) < 0) {
    // Serial.print("Position decreased: ");
    // Serial.println(newPos);
    Keyboard.release('2');
    Keyboard.press('1');
    isRotateVolL = true;
    startTimeVolL = millis();
  }
  // 돌아가지 않았다
  else {
    unsigned long interTime = millis();
    if ((interTime - startTimeVolL > ENCODER_TIME) && (isRotateVolL == true)) {
      isRotateVolL = false;
      // Serial.println("Encoder stopped rotating");
      // 키보드 입력 해제 코드
      Keyboard.release('1');
      Keyboard.release('2');
    }
  }
  
  posVolL = newPos;  
}

void functionBTA() {
  if (digitalRead(BTA) == LOW) {
    Keyboard.press("d");
    digitalWrite(BTA_LED, HIGH);
  }
  else {
    Keyboard.release("d");
    digitalWrite(BTA_LED, LOW);
  }
}

void functionBTB() {
  if (digitalRead(BTB) == LOW) {
    Keyboard.press("f");
    digitalWrite(BTB_LED, HIGH);
  }
  else {
    Keyboard.release("f");
    digitalWrite(BTB_LED, LOW);
  }  
}

void functionBTC() {
  if (digitalRead(BTC) == LOW) {
    Keyboard.press("j");
    digitalWrite(BTC_LED, HIGH);
  }
  else {
    Keyboard.release("j");
    digitalWrite(BTC_LED, LOW);
  }  
}

void functionBTD() {
  if (digitalRead(BTD) == LOW) {
    Keyboard.press("k");
    digitalWrite(BTD_LED, HIGH);
  }
  else {
    Keyboard.release("k");
    digitalWrite(BTD_LED, LOW);
  }  
}
