#include <ESP8266WiFi.h>
#include <time.h> // 使用 NTP 时间同步

// Wi-Fi 信息
const char* ssid = "Reiki_Desktop";
const char* password = "Reikimen";

// NTP 服务器和时区信息
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;         // GMT 偏移量（秒）
const int daylightOffset_sec = 3600; // 夏令时偏移量（秒）

// 控制线程间隔
int wificounter = 10; // 第一次在10ms检查WiFi并且开始连接，之后每20s检查一次
int timecounter = 1000;

// 时间变量
time_t now;
struct tm timeinfo;

void WifiConnectionThread() {
  wificounter--;
  if (wificounter <= 0) {
    wificounter = 20000; // 每20s检查一次
    if (WiFi.status() != WL_CONNECTED) {
      // 连接 WiFi
      WiFi.begin(ssid, password);
      Serial.println("Connecting Wifi...");

      if (WiFi.waitForConnectResult() == WL_CONNECTED) {
        Serial.println("WiFi connected!");

        // 初始化 NTP 时间同步（非阻塞）
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        Serial.println("NTP setup initialized.");
      } else {
        Serial.println("WiFi connection failed.");
      }
    } else {
      Serial.println("WiFi is OK!");
    }
  }
}

void WorldTimerThread() {
  timecounter--;
  if (timecounter <= 0) {
    timecounter = 1000;

    // 获取当前时间
    time(&now);
    localtime_r(&now, &timeinfo);

    if (timeinfo.tm_year > (1970 - 1900)) { // 确保时间已同步
      char londonTimeStr[64];
      char chinaTimeStr[64];

      // 格式化时间字符串（替换为不同时区）
      strftime(londonTimeStr, sizeof(londonTimeStr), "%Y-%m-%d %H:%M:%S", &timeinfo);
      
      // 修改 tm 结构体的时区（示例中未做实际调整，需自行实现）
      strftime(chinaTimeStr, sizeof(chinaTimeStr), "%Y-%m-%d %H:%M:%S", &timeinfo); 

      Serial.println("London Time: " + String(londonTimeStr));
      Serial.println("China Time: " + String(chinaTimeStr));
    } else {
      Serial.println("Time not synchronized yet.");
    }
  }
}
