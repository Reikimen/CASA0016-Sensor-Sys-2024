#include <ESP8266WiFi.h>
#include <ezTime.h>

// Wi-Fi 信息
const char* ssid = "Reiki_Desktop";
const char* password = "Reikimen";

// 创建时区对象
Timezone londonTZ;
Timezone chinaTZ;

void setup() {
  Serial.begin(115200);
  delay(100);

  // 连接 Wi-Fi
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);  // 以station模式连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // 初始化 NTP
  Serial.println("Synchronizing time with NTP...");
  setDebug(INFO);       // 打印详细调试信息，可注释掉
  waitForSync();        // 同步时间
  Serial.println("Time synchronized!");

  // 设置时区
  londonTZ.setLocation("Europe/London");  // 伦敦时区
  chinaTZ.setLocation("Asia/Shanghai");  // 中国时区
}

void loop() {
  // 获取当前时间
  String londonTime = londonTZ.dateTime("Y-m-d H:i:s (T)"); // 格式：年-月-日 时:分:秒 (时区)
  String chinaTime = chinaTZ.dateTime("Y-m-d H:i:s (T)");

  // 打印时间
  Serial.println("Time in London: " + londonTime);
  Serial.println("Time in China: " + chinaTime);
  Serial.println();

  delay(1000); // 每秒更新一次
}
