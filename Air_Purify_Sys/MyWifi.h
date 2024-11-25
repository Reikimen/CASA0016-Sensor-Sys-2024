void InitilizeWiFiNTP() {
  Serial.println("");
  WiFi.mode(WIFI_STA);
  if (WiFi.status() != WL_CONNECTED) {
    // Start Connecting Wifi
    WiFi.begin(ssid, password);
    Serial.println("Start Connecting Wifi!");
    
    // Continuously waiting to connect to WiFi and jumping out of the dead loop when the connection is successful
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println("Connecting Wifi...");
      delay(200);
    }

    // initizal NTP
    Serial.println("Synchronizing time with NTP...");
    // setDebug(INFO);        // Prints detailed debugging information, which can be commented out.
    waitForSync();            // Synchronise time, seems to block other programs when NTP is connected.
    Serial.println("Time synchronized!");

    // Set time zone
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