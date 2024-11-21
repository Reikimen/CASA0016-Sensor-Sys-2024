// v0.3
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "ritos.h" // https://github.com/0ingchun/RITOS-lib-Arduino
#include "MyConfig.h"
// #include "MyWifi.h"
// #include "MyWifi114514.h"
#include "MyLCD.h"
#include "MyCtrlLogic.h" // 我是: 唱跳Rap篮球高手
#include "MySensors.h"

// 线程任务声明
// Ritos taskWIFI;
// Ritos taskTimer;
Ritos taskLCD;
Ritos taskEncoder;
Ritos taskCheckEncoder; 
Ritos taskButton;
Ritos taskHomeButton;

void setup() {
  Serial.begin(115200);
  // Initilize the mode of WiFi
  // WiFi.mode(WIFI_STA);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Initialize the pin for encoder
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderPinBtn, INPUT_PULLUP);

  // Initialize the pin for HomeBtn
  pinMode(homeBtnPin, INPUT_PULLUP);

  delay(100);

  // Create threads
  // taskWIFI.task(WifiConnectionThread);
  // taskTimer.task(WorldTimerThread);
  taskLCD.task(LCDThread);
  taskEncoder.task(encoderThread);
  taskCheckEncoder.task(CheckEncoderThread);
  taskButton.task(buttonThread);
  taskHomeButton.task(homeBtnThread);
}

void loop() {
  // Empty, all logic is executed in the thread
}
