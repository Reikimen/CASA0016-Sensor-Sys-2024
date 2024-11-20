#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "ritos.h" // https://github.com/0ingchun/RITOS-lib-Arduino

int DISPLAYMODE = 0;
#include "MyLCD.h"
#include "MyEncoder.h"

// 线程任务声明
Ritos taskLCD;
Ritos taskEncoder;
Ritos taskButton;

void setup() {
  Serial.begin(115200);

  // 初始化引脚
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderBtn, INPUT_PULLUP);

  // 初始化LCD
  lcd.init();
  lcd.backlight();

  delay(200);

  // 创建线程
  taskLCD.task(LCDThread);
  taskEncoder.task(encoderThread);
  taskButton.task(buttonThread);
}

void loop() {
  // 空，所有逻辑在线程中执行
}
