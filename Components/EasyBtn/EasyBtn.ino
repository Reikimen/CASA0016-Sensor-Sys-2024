#define BUTTON_PIN 0  // 定义按钮引脚 D3

void setup() {
  Serial.begin(115200);                 // 初始化串口监视器
  pinMode(BUTTON_PIN, INPUT_PULLUP);    // 将引脚模式设为输入，启用内部上拉
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);  // 读取按钮状态
  if (buttonState == LOW) {                   // 按钮被按下
    Serial.println("Button Pressed");
  } else {                                    // 按钮未按下
    Serial.println("Button Released");
  }
  delay(100);  // 延迟 100 毫秒，防止串口输出太快
}
