// Wi-Fi 信息
const char* ssid = "Reiki_Desktop";
const char* password = "Reikimen";

// 创建时区对象
Timezone londonTZ;
Timezone chinaTZ;

// 控制WifiConnectionThread和WorldTimerThread的间隔
int wificounter = 10; // 第一次在10ms检查WiFi并且开始连接，之后每20s检查一次
int timecounter = 1000;

String londonTime = londonTZ.dateTime("Y-m-d H:i:s (T)");
String chinaTime = chinaTZ.dateTime("Y-m-d H:i:s (T)");

void WifiConnectionThread() {
  wificounter--;
  if (wificounter <= 0){
    wificounter = 20000; // 每20s检查一次
    if (WiFi.status() != WL_CONNECTED) {
      // 连接WIFI
      WiFi.begin(ssid, password);
      Serial.println("Connecting Wifi...?!");

      // 初始化 NTP
      Serial.println("Synchronizing time with NTP...");
      // setDebug(INFO);       // 打印详细调试信息，可注释掉
      waitForSync();        // 同步时间, 似乎当WIFI连接时会阻断其他程序运行
      Serial.println("Time synchronized!");

      // 设置时区
      londonTZ.setLocation("Europe/London");
      chinaTZ.setLocation("Asia/Shanghai");
    }
    else Serial.println("Wifi is OK!");
  }
}

void WorldTimerThread() {
  timecounter--;
  if (timecounter <= 0){
    timecounter = 1000;
    Serial.println("London Time: " + londonTime);
    Serial.println("China Time: " + chinaTime);
  }
}