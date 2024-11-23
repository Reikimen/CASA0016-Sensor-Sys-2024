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
    timecounter = CONSTTIMECOUNT;
    londonST = londonTZ.dateTime("(T)");
    londonDate = londonTZ.dateTime("Y-m-d");
    londonTime = londonTZ.dateTime("H:i:s");
    chinaST = chinaTZ.dateTime("(T)");
    chinaDate = chinaTZ.dateTime("Y-m-d");
    chinaTime = chinaTZ.dateTime("H:i:s");

    Serial.println("London Time: " + londonDate + " " + londonTime + " " + londonST);
    Serial.println("China Time: " + chinaDate + " " + chinaTime + " " + londonST);
  }
}