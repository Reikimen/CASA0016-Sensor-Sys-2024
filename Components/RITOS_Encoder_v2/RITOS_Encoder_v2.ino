#define encoderPinA 12  // D6
#define encoderPinB 13  // D7
#define encoderBtn 14   // D5

#include "ritos.h" // https://github.com/0ingchun/RITOS-lib-Arduino

volatile int encoderPosition = 0;   // 保存旋转计数
volatile bool buttonPressed = false;  // 按钮按下状态

// 线程任务声明
Ritos taskEncoder;
Ritos taskCheckEncoder;
Ritos taskButton;

// 去抖动时间
#define DEBOUNCE_TIME 50  
unsigned long lastDebounceTime = 0;

// 编码器状态
int lastEncoderStateA = LOW;
int lastEncoderStateB = LOW;

// 按钮状态
int lastButtonState = HIGH;

int encodercount = 10;
int buttoncount = 10;

void encoderThread() {

  int currentStateA = digitalRead(encoderPinA);
  int currentStateB = digitalRead(encoderPinB);

  // 检测到旋转
  if (lastEncoderStateA == LOW && currentStateA == HIGH) {
    if (currentStateB == LOW) {
      encoderPosition--;  // 左旋
      //Serial.println("Rotated Left");
    } else {
      encoderPosition++;  // 右旋
      //Serial.println("Rotated Right");
    }
  }

  // 更新状态
  lastEncoderStateA = currentStateA;
  lastEncoderStateB = currentStateB;
}

void checkencoderThread(){
  encodercount--;
  if (encodercount<=0){
    encodercount = 10;
    if (encoderPosition < 0){
      Serial.println("Rotated Left");
    }
    // else if (encoderPosition == 0) {
    //   Serial.println("");
    // }
    // else {
    //   Serial.println("Rotated Right");
    // }
    if (encoderPosition > 0){
      Serial.println("Rotated Right");
    }

    // 重归 encoderPosition 为 0
    encoderPosition = 0;
  }
}

void buttonThread() {
  int currentButtonState = digitalRead(encoderBtn);

  // 去抖检测
  if (currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
    // 按钮状态变化检测
    if (currentButtonState == LOW && !buttonPressed) {
      buttonPressed = true;
      Serial.println("Button Pressed");
    } else if (currentButtonState == HIGH && buttonPressed) {
      buttonPressed = false;
      Serial.println("Button Released");
    }
  }

  // 更新按钮状态
  lastButtonState = currentButtonState;
}

void setup() {
  Serial.begin(115200);

  // 初始化引脚
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderBtn, INPUT_PULLUP);

  // 创建线程
  taskEncoder.task(encoderThread);
  taskCheckEncoder.task(checkencoderThread);
  taskButton.task(buttonThread);
}

void loop() {
  // 空，所有逻辑在线程中执行
}
