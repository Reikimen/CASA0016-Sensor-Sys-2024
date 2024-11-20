#define encoderPinA 12  // D6
#define encoderPinB 13  // D7
#define encoderBtn 14   // D5

// 去抖动时间
#define DEBOUNCE_TIME 50  
unsigned long lastDebounceTime = 0;

// 保存旋转计数, 按钮按下状态
volatile int encoderPosition = 0;
volatile bool buttonPressed = false;

// 编码器状态
int lastEncoderStateA = LOW;
int lastEncoderStateB = LOW;

// 旋转方向，逆时针（左旋）为 1，顺时针（右旋）为 0，默认为 11451
int EncoderRotate = 11451;

// 按钮状态，默认空引脚高电平
int lastButtonState = HIGH;

void modeLogic(){
  switch (DISPLAYMODE){
    case 0:
      if (EncoderRotate == 0) DISPLAYMODE = 1;
      else if (EncoderRotate == 1) DISPLAYMODE = 1;
      if (buttonPressed) DISPLAYMODE = 1;
      break;
    case 1:
      if (EncoderRotate == 0) DISPLAYMODE = 2;
      else if (EncoderRotate == 1) DISPLAYMODE = 1;
      if (buttonPressed) DISPLAYMODE = 1;
      break;
    case 2:
      if (EncoderRotate == 0) DISPLAYMODE = 3;
      else if (EncoderRotate == 1) DISPLAYMODE = 1;
      if (buttonPressed) DISPLAYMODE = 1;
      break;
    case 3:
      if (EncoderRotate == 0) DISPLAYMODE = 6;
      else if (EncoderRotate == 1) DISPLAYMODE = 2;
      if (buttonPressed) DISPLAYMODE = 1;
      break;
    case 4:
      if (EncoderRotate == 0) DISPLAYMODE = 5;
      else if (EncoderRotate == 1) DISPLAYMODE = 1;
      if (buttonPressed) DISPLAYMODE = 1;
      break;
    case 5:
      if (EncoderRotate == 0) DISPLAYMODE = 6;
      else if (EncoderRotate == 1) DISPLAYMODE = 4;
      if (buttonPressed) DISPLAYMODE = 1;
      break;
    case 6:
      if (EncoderRotate == 0) DISPLAYMODE = 9;
      else if (EncoderRotate == 1) DISPLAYMODE = 5;
      if (buttonPressed) DISPLAYMODE = 1;
      break;
    case 7:
      if (EncoderRotate == 0) DISPLAYMODE = 8;
      else if (EncoderRotate == 1) DISPLAYMODE = 4;
      if (buttonPressed) DISPLAYMODE = 1;
      break;
    case 8:
      if (EncoderRotate == 0) DISPLAYMODE = 9;
      else if (EncoderRotate == 1) DISPLAYMODE = 7;
      if (buttonPressed) DISPLAYMODE = 1;
      break;
    case 9:
      if (EncoderRotate == 0) DISPLAYMODE = 9;
      else if (EncoderRotate == 1) DISPLAYMODE = 8;
      if (buttonPressed) DISPLAYMODE = 1;
      break;
    default:
      break;
  }
}

void encoderThread() {
  int currentStateA = digitalRead(encoderPinA);
  int currentStateB = digitalRead(encoderPinB);

  // 检测旋转，Serial回传，改变 LCD mode
  if (lastEncoderStateA == LOW && currentStateA == HIGH) {
    if (currentStateB == LOW) {// 左旋
      encoderPosition--;
      EncoderRotate = 1;
      Serial.println("Rotated Left");
    } 
    else {// 右旋
      encoderPosition++;
      EncoderRotate = 0;
      Serial.println("Rotated Right");
    }
    modeLogic(); // 根据获得的旋转方向信息，更改 LCD mode
  }

  // 更新状态
  lastEncoderStateA = currentStateA;
  lastEncoderStateB = currentStateB;
  // 消除旋转方向
  EncoderRotate = 11451;
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
      modeLogic();
    } 
    else if (currentButtonState == HIGH && buttonPressed) {
      buttonPressed = false;
      Serial.println("Button Released");
    }
  }

  // 更新按钮状态
  lastButtonState = currentButtonState;
}