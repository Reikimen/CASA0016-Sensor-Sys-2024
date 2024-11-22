// Wi-Fi 信息
const char* ssid = "Reiki_Desktop";
const char* password = "Reikimen";

// 创建时区对象
Timezone londonTZ;
Timezone chinaTZ;

// WorldTimerThread的间隔
int timecounter = 1000;

void InitilizeWiFiNTP() {
  Serial.println("");
  WiFi.mode(WIFI_STA);
  if (WiFi.status() != WL_CONNECTED) {
    // 连接WIFI
    WiFi.begin(ssid, password);
    Serial.println("Start Connecting Wifi!");
    
    // 持续等待连接WiFi，连接成功后跳出死循环
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println("Connecting Wifi...");
      delay(200);
    }

    // 初始化 NTP
    Serial.println("Synchronizing time with NTP...");
    // setDebug(INFO);       // 打印详细调试信息，可注释掉
    waitForSync();        // 同步时间, 似乎当NTP连接时会阻断其他程序运行
    Serial.println("Time synchronized!");

    // 设置时区
    londonTZ.setLocation("Europe/London");
    chinaTZ.setLocation("Asia/Shanghai");
  }
  else Serial.println("Wifi is OK!");
}

void WorldTimerThread() {
  timecounter--;
  if (timecounter <= 0){
    timecounter = 1000;
    String londonTime = londonTZ.dateTime("Y-m-d H:i:s (T)");
    String chinaTime = chinaTZ.dateTime("Y-m-d H:i:s (T)");

    Serial.println("London Time: " + londonTime);
    Serial.println("China Time: " + chinaTime);
  }
}