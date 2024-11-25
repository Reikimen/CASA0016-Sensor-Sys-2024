#include <Wire.h>

// SHT30 默认 I²C 地址
#define SHT30_ADDR 0x44

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

unsigned long previousMillis = 0; // 上次测量的时间
const unsigned long measurementInterval = 500; // 测量间隔 500 毫秒

enum SensorState {
  IDLE,
  WAITING_FOR_MEASUREMENT,
  READY
};

SensorState currentState = IDLE;

void setup() {
  Wire.begin(); // 初始化 I²C
  Serial.begin(115200);
  Serial.println("初始化 SHT30...");
}

void loop() {
  unsigned long currentMillis = millis();

  switch (currentState) {
    // IDLE: 初始化或发送测量命令。
    // WAITING_FOR_MEASUREMENT: 等待测量完成。
    // READY: 读取并处理数据。
    case IDLE:
      // 发送测量命令
      Wire.beginTransmission(SHT30_ADDR);
      Wire.write(0x2C);
      Wire.write(0x06);
      Wire.endTransmission();

      previousMillis = currentMillis;
      currentState = WAITING_FOR_MEASUREMENT;
      break;

    case WAITING_FOR_MEASUREMENT:
      if (currentMillis - previousMillis >= measurementInterval) {
        currentState = READY;
      }
      break;

    case READY:
      // 读取测量数据
      Wire.requestFrom(SHT30_ADDR, 6);
      if (Wire.available() == 6) {
        uint8_t data[6];
        for (uint8_t i = 0; i < 6; i++) {
          data[i] = Wire.read();
        }

        // 校验 CRC
        if (calculateCRC(data, 2) != data[2] || calculateCRC(data + 3, 2) != data[5]) {
          Serial.println("CRC 校验失败！");
          currentState = IDLE;
          break;
        }

        // 转换原始数据为温湿度
        uint16_t rawTemp = (data[0] << 8) | data[1];
        uint16_t rawHum = (data[3] << 8) | data[4];

        float temperature = -45 + 175 * ((float)rawTemp / 65535.0);
        float humidity = 100 * ((float)rawHum / 65535.0);

        // 打印结果
        Serial.print("温度: ");
        Serial.print(temperature);
        Serial.print(" °C\t湿度: ");
        Serial.print(humidity);
        Serial.println(" %");
      } else {
        Serial.println("读取失败！");
      }
      currentState = IDLE; // 返回到初始状态，准备下次测量
      break;
  }

  // 其他非阻塞操作可以放在这里
}
