#include <Wire.h>  // 引入I2C库

// SHT30传感器的I2C地址
#define Addr_SHT30 0x44

// 存储SHT30测量数据的变量
uint8_t sht30_data[6];
float sht30_cTemp;     // 摄氏温度
float sht30_fTemp;     // 华氏温度
float sht30_humidity;  // 相对湿度

void setup() {
  // 初始化串口通讯
  Serial.begin(115200);
  while (!Serial) {
    ;  // 等待串口就绪
  }

  // 初始化I2C通信
  Wire.begin();
  Serial.println("SHT30测量程序初始化完成！");
}

void loop() {
  // 调用测量函数
  measure_sht30();

  // 延时5秒再进行下一次测量
  delay(5000);
}

void measure_sht30() {
  // 发送测量命令 0x2C06
  Wire.beginTransmission(Addr_SHT30);
  Wire.write(0x2C);
  Wire.write(0x06);
  Wire.endTransmission();
  delay(100);  // 等待SHT30测量完成

  // 请求获取6字节的数据
  Wire.requestFrom(Addr_SHT30, 6);

  // 读取6字节的数据
  if (Wire.available() == 6) {
    sht30_data[0] = Wire.read();
    sht30_data[1] = Wire.read();
    sht30_data[2] = Wire.read();  // CRC校验数据，目前未用
    sht30_data[3] = Wire.read();
    sht30_data[4] = Wire.read();
    sht30_data[5] = Wire.read();  // CRC校验数据，目前未用
  } else {
    Serial.println("数据读取失败，请检查传感器连接！");
    return;
  }

  // 计算温度和湿度
  sht30_cTemp = ((((sht30_data[0] * 256.0) + sht30_data[1]) * 175) / 65535.0) - 45;
  sht30_fTemp = (sht30_cTemp * 1.8) + 32;
  sht30_humidity = ((((sht30_data[3] * 256.0) + sht30_data[4]) * 100) / 65535.0);

  // 输出数据到串口
  Serial.print("相对湿度：");
  Serial.print(sht30_humidity);
  Serial.println(" %RH");
  Serial.print("摄氏度温度：");
  Serial.print(sht30_cTemp);
  Serial.println(" C");
  Serial.print("华氏度温度：");
  Serial.print(sht30_fTemp);
  Serial.println(" F");
}
