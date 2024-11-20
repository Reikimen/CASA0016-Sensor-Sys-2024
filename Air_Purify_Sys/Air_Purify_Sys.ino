// v0.2
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "ritos.h" // https://github.com/0ingchun/RITOS-lib-Arduino

int DISPLAYMODE = 0;
#include "MyBufferLCD.h"
#include "MyEncoder.h"

// 线程任务声明
Ritos taskLCD;
Ritos taskEncoder;
Ritos taskCheckEncoder; 
Ritos taskButton;

void setup() {
  Serial.begin(115200);

  // Initialize the pin for encoder
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderBtn, INPUT_PULLUP);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  delay(50);

  // Create threads
  taskLCD.task(LCDThread);
  taskEncoder.task(encoderThread);
  taskCheckEncoder.task(CheckEncoderThread);
  taskButton.task(buttonThread);
}

void loop() {
  // Empty, all logic is executed in the thread
}
