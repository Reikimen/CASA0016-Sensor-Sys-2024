#include <Wire.h>
#include "ritos.h"

// SHT30 默认 I²C 地址
#define SHT30_ADDR 0x44

volatile int SHT30count = 0; // 用于计时 SHT30 的读取间隔

Ritos sht30Thread; // 创建 SHT30 线程任务

// CRC 校验函数
uint8_t calculateCRC(uint8_t data[], uint8_t length) {
  uint8_t crc = 0xFF; // 初始值
  const uint8_t polynomial = 0x31; // 多项式 x^8 + x^5 + x^4 + 1

  for (uint8_t i = 0; i < length; i++) {
    crc ^= data[i];
    for (uint8_t bit = 8; bit > 0; --bit) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ polynomial;
      } else {
        crc = (crc << 1);
      }
    }
  }
  return crc;
}

// SHT30 数据读取函数
void readSHT30() {
  // 发送测量命令
  Wire.beginTransmission(SHT30_ADDR);
  Wire.write(0x2C);
  Wire.write(0x06);
  Wire.endTransmission();

  // 请求 6 字节数据
  Wire.requestFrom(SHT30_ADDR, 6);
  if (Wire.available() == 6) {
    uint8_t data[6];
    for (uint8_t i = 0; i < 6; i++) {
      data[i] = Wire.read();
    }

    // 校验 CRC
    if (calculateCRC(data, 2) != data[2] || calculateCRC(data + 3, 2) != data[5]) {
      Serial.println("SHT30: CRC 校验失败！");
      return;
    }

    // 转换原始数据为温湿度
    uint16_t rawTemp = (data[0] << 8) | data[1];
    uint16_t rawHum = (data[3] << 8) | data[4];

    float temperature = -45 + 175 * ((float)rawTemp / 65535.0);
    float humidity = 100 * ((float)rawHum / 65535.0);

    // 打印温湿度数据
    Serial.print("温度: ");
    Serial.print(temperature);
    Serial.print(" °C\t湿度: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("SHT30: 数据读取失败！");
  }
}

// SHT30 线程函数
void sht30Task() {
  SHT30count--; // 计时器减小
  if (SHT30count <= 0) {
    Serial.println("SHT30 线程触发！");
    readSHT30();       // 调用读取函数
    SHT30count = 500;  // 设置下一次触发计时（500ms，约等于 0.5 秒）
  }
}

// 初始化函数
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); // 初始化 LED

  Wire.begin(); // 初始化 I²C

  // 创建线程任务
  sht30Thread.task(sht30Task); // 创建 SHT30 数据读取线程
}

void loop() {
  // 主循环不执行任何任务，所有任务交给线程处理
}
