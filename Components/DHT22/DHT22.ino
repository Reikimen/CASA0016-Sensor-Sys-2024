#include <DHT.h>

// 定义 DHT 类型和引脚
#define DHTPIN 2 // 使用 GPIO15
#define DHTTYPE DHT22 // DHT22 类型

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("DHT22 温湿度传感器初始化");
  dht.begin();
}

void loop() {
  // 读取湿度和温度
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // 检查是否成功读取
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("读取 DHT22 数据失败!");
    return;
  }

  // 打印数据
  Serial.print("湿度: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("温度: ");
  Serial.print(temperature);
  Serial.println(" *C");

  delay(2000); // 每 2 秒读取一次
}
