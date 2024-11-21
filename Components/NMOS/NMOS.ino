void setup() {
  // 设置引脚13为输出模式
  pinMode(16, OUTPUT);
}

void loop() {
  // 设置引脚13为高电平（5V 或 3.3V，具体取决于板子的电压）
  digitalWrite(16, HIGH);                                                                                                                                                                                                                                                          
  delay(1000);  // 延时1秒

  // 设置引脚13为低电平（0V）
  digitalWrite(16, LOW);
  delay(1000);  // 延时1秒
}
