#include "MQ135.h"

MQ135 gasSensor = MQ135(A0); // 传感器接到 A0 引脚

void setup() {
  Serial.begin(115200);
  Serial.println("MQ135 Multi-Gas Detection");
}

void loop() {
  float rzero = gasSensor.getRZero();     // 获取空气中的基准值 R₀
  float rs = gasSensor.getResistance();  // 获取传感器瞬时电阻 Rs

  // CO2 浓度 (PPM)
  float co2_ppm = calculateGasConcentration(rs, rzero, 110.47, -2.62);
  Serial.print("CO2 (ppm): ");
  Serial.println(co2_ppm);

  // NH3 (氨气) 浓度 (PPM)
  float nh3_ppm = calculateGasConcentration(rs, rzero, 116.602, -2.769);
  Serial.print("NH3 (ppm): ");
  Serial.println(nh3_ppm);

  // 烟雾/一氧化碳浓度 (PPM)
  float smoke_ppm = calculateGasConcentration(rs, rzero, 102.2, -2.473);
  Serial.print("Smoke/CO (ppm): ");
  Serial.println(smoke_ppm);

  delay(2000); // 每2秒更新一次
}

// 通用气体浓度计算函数
float calculateGasConcentration(float rs, float rzero, float a, float b) {
  float ratio = rs / rzero; // 计算 Rs/R0 的比例
  return a * pow(ratio, b); // 使用公式计算浓度
}
