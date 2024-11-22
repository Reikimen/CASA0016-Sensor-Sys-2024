void setup() {
  // GPIO2 D4
  pinMode(2, OUTPUT);
}

void loop() {
  // 设置引脚13为高电平（5V 或 3.3V，具体取决于板子的电压）
  digitalWrite(2, HIGH);                                                                                                                                                                                                                                                          
  delay(10000);  // 延时1秒

  // 设置引脚13为低电平（0V）
  digitalWrite(2, LOW);
  delay(10000);  // 延时1秒
}
