#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// pins (match wiring)
const int touchPin = 2;    // button -> GND (use INPUT_PULLUP)
const int buzzerPin = 8;
const int redPin = 3;      // PWM
const int greenPin = 5;    // PWM
const int bluePin = 6;     // PWM
const int potPin = A0;     // brightness control

// state
int expression = 0;
int lastState = HIGH;
unsigned long lastDebounce = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(touchPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 init failed");
    for (;;) ;
  }
  display.clearDisplay();
  drawExpression(expression);
}

void loop() {
  // ---------------- button with debounce ----------------
  int reading = digitalRead(touchPin);
  if (reading != lastState) {
    lastDebounce = millis();
  }
  if ((millis() - lastDebounce) > debounceDelay) {
    // stable reading
    if (lastState == HIGH && reading == LOW) { // pressed (INPUT_PULLUP)
      expression = (expression + 1) % 4;
      tone(buzzerPin, 800, 110); // beep
      drawExpression(expression);
    }
  }
  lastState = reading;

  // update peripherals each loop
  applyRGB(expression);
  applyBrightness();

  // small delay to reduce CPU usage
  delay(10);
}

// ----- draw expressions -----

void drawExpression(int e) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  switch (e) {
    case 0: display.println("MOOD: HAPPY"); drawHappy(); break;
    case 1: display.println("MOOD: ANGRY"); drawAngry(); break;
    case 2: display.println("MOOD: SURPRISED"); drawSurprised(); break;
    case 3: display.println("MOOD: NEUTRAL"); drawNeutral(); break;
    default: display.println("MOOD: ?"); drawNeutral(); break;
  }
  display.display();
}

void drawHappy() {
  display.fillCircle(40, 25, 7, WHITE);
  display.fillCircle(88, 25, 7, WHITE);
  display.fillCircle(40, 25, 3, SSD1306_BLACK);
  display.fillCircle(88, 25, 3, SSD1306_BLACK);
  display.drawCircle(64, 48, 20, WHITE);
  display.fillRect(46, 34, 36, 16, SSD1306_BLACK);
  display.drawLine(52, 51, 76, 51, WHITE);
}

void drawAngry() {
  display.drawLine(26,16,46,24,WHITE);
  display.drawLine(102,16,82,24,WHITE);
  display.fillCircle(40, 30, 6, WHITE);
  display.fillCircle(88, 30, 6, WHITE);
  display.fillCircle(40, 30, 3, SSD1306_BLACK);
  display.fillCircle(88, 30, 3, SSD1306_BLACK);
  display.drawLine(46, 55, 82, 55, WHITE);
}

void drawSurprised() {
  display.drawCircle(40, 24, 8, WHITE);
  display.drawCircle(88, 24, 8, WHITE);
  display.fillCircle(40, 24, 2, SSD1306_WHITE);
  display.fillCircle(88, 24, 2, SSD1306_WHITE);
  display.drawCircle(64, 47, 10, WHITE);
}

void drawNeutral() {
  display.fillCircle(40, 25, 6, WHITE);
  display.fillCircle(88, 25, 6, WHITE);
  display.fillCircle(40, 25, 2, SSD1306_BLACK);
  display.fillCircle(88, 25, 2, SSD1306_BLACK);
  display.drawLine(48, 50, 80, 50, WHITE);
}

// ----- hardware helpers -----

void applyRGB(int expr) {
  switch (expr) {
    case 0: // happy -> green
      analogWrite(redPin, 0);
      analogWrite(greenPin, 200);
      analogWrite(bluePin, 0);
      break;
    case 1: // angry -> red
      analogWrite(redPin, 200);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      break;
    case 2: // surprised -> blue
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 200);
      break;
    case 3: // neutral -> yellowish
      analogWrite(redPin, 140);
      analogWrite(greenPin, 110);
      analogWrite(bluePin, 0);
      break;
  }
}

void applyBrightness() {
  int potValue = analogRead(potPin);
  int contrast = map(potValue, 0, 1023, 10, 255);
  // set SSD1306 contrast
  display.ssd1306_command(0x81);
  display.ssd1306_command(contrast);
}
