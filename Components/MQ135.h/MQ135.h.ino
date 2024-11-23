#include "MQ135.h"

MQ135 gasSensor = MQ135(A0);

void setup() {
  Serial.begin(115200); // 使用更快的串口速度
  Serial.println("Calibrating sensor...");

  // 可选：等待传感器预热，建议 24-48 小时预热
  delay(2000);

  // 校准 R0 值
  float rzero = gasSensor.getRZero();
  Serial.print("Calibrated RZero = ");
  Serial.println(rzero);
}

void loop() {
  // 获取实时 R0 值
  float rzero = gasSensor.getRZero();

  // 计算气体浓度（ppm）
  float ppm = gasSensor.getPPM();

  // 输出结果
  Serial.print("RZero: ");
  Serial.print(rzero);
  Serial.print(" | CO2 Concentration (PPM): ");
  Serial.println(ppm);

  delay(1000); // 每秒更新一次
}
