// Nothing Now

// #include <DHT.h>

// // 定义 DHT 类型和引脚
// #define DHTPIN 2 // 使用 GPIO2 D4
// #define DHTTYPE DHT22 // DHT22 类型

// DHT dht22(DHTPIN, DHTTYPE);

// int DHT22count = 1000;

// void DHT22Thread() {
//   DHT22count--;
//   if (DHT22count <= 0){
//     DHT22count = 1000;
//     // 读取湿度和温度
//   float temp = dht22.readTemperature();
//   float hum = dht22.readHumidity();
//   if (!isnan(temp) && !isnan(hum)) {
//     Serial.print("温度: "); Serial.println(temp);
//     Serial.print("湿度: "); Serial.println(hum);
//   } else {
//     Serial.println("读取失败！");
//   }
//   }

// }

// MQ135
// 通用气体浓度计算函数 for MQ135
float calculateGasConcentration(float rs, float rzero, float a, float b) {
  float ratio = rs / rzero; // 计算 Rs/R0 的比例
  return a * pow(ratio, b); // 使用公式计算浓度
}
void MQ135Thread(){
  MQ135count--;
  if (MQ135count <= 0){
    MQ135count = 2000;

    rzero = SensorMQ135.getRZero();     // 获取空气中的基准值 R₀
    rs = SensorMQ135.getResistance();  // 获取传感器瞬时电阻 Rs

    // CO2 浓度 (PPM)
    co2_ppm = calculateGasConcentration(rs, rzero, 110.47, -2.62);
    Serial.print("CO2 (ppm): ");
    Serial.println(co2_ppm);
  }
}