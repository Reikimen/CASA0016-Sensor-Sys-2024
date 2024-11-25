// LCD2004 and NOMS&FAN

// Dual buffering mechanism to minimize I2C communication time
// The LCD is updated via LCD.setcursor () and LCD.print () only when the content changes, avoiding unnecessary I2C communication and optimizing performance.
void LCDThread(){
  LCDcount--;
  if (LCDcount <= 0){
    LCDcount = CONSTLCDCOUNT;

    char tempBuffer[4][21] = {0}; // Temporary buffer to store new content
    switch (DISPLAYMODE){
      // Hello Dankao, this screen will continue until the rotary encoder is pressed or turned, and jump to case 1.
      case 0:
        strcpy(tempBuffer[0], "Hello World!  it's ");
        strcpy(tempBuffer[1], "   Dankao Kingdom  ");
        strcpy(tempBuffer[2], "Press or Rotate The ");
        strcpy(tempBuffer[3], "Encoder for Continue");
        break;
      // 
      // Encoder rotates to the right and does not allow further rotation after the end.
      // Encoder rotates to the left and does not allowed to rotate after the end.
      case 1: // Right：case 2，left：case 1，按下Encoder case 13
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|TIME| |T&RH| | PM |");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "  <>                ");
        break;

      case 2: // Right：case 3，left：case 1，按下Encoder case 14
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|TIME| |T&RH| | PM |");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "         <>         ");
        break;

      case 3:  // Right：case 6，left：case 2，按下Encoder case 15
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|TIME| |T&RH| | PM |");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "                <>  ");
        break;

      case 4:  // Right：case 5，left：case 1，按下Encoder case 14
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|T&RH| | PM | | AQI|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "  <>                ");
        break;

      case 5:  // Right：case 6，left：case 4，按下Encoder case 15
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|T&RH| | PM | | AQI|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "         <>         ");
        break;
      
      case 6:  // Right：case 9，left：case 5，按下Encoder case 16
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|T&RH| | PM | | AQI|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "                <>  ");
        break;

      case 7:  // Right：case 8，left：case 4，按下Encoder case 15
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "| PM | | AQI| |FANs|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "  <>                ");
        break;

      case 8:  // Right：case 9，left：case 7，按下Encoder case 16
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "| PM | | AQI| |FANs|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "         <>         ");
        break;
        
      case 9:  // Right：case 9，left：case 8，按下Encoder case 10
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "| PM | | AQI| |FANs|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "                <>  ");
        break;

      // The following fan modes are selected from case 10 to case 12.
      // The mode is whatever the screen is in, no need to double check, only responds to rotate left/right and press HomeBtn.
      case 10:  // Right：case 11，left：case 10，
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|AUTO| | ON | | OFF|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "  <>                ");
        break;

      case 11:  // Right：case 12，left：case 10，
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|AUTO| | ON | | OFF|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "         <>         ");
        break;

      case 12:  // Right：case 12，left：case 11，
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|AUTO| | ON | | OFF|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "                <>  ");
        break;

      // The following modes display time, sensors, etc. and respond only to HomeBtn
      case 13:
        sprintf(tempBuffer[0], "London:%s        ", londonST.c_str());
        sprintf(tempBuffer[1], "%s %s ", londonDate.c_str(), londonTime.c_str());
        sprintf(tempBuffer[2], "China :%s        ", chinaST.c_str());
        sprintf(tempBuffer[3], "%s %s ", chinaDate.c_str(), chinaTime.c_str());
        break;

      case 14:
        strcpy(tempBuffer[0], "Temp and Humidty    ");
        snprintf(tempBuffer[1], sizeof(tempBuffer[1]), "cTemp:    %4.2f *C   ", sht30_cTemp);
        snprintf(tempBuffer[2], sizeof(tempBuffer[2]), "fTemp:    %4.2f *F   ", sht30_fTemp);
        snprintf(tempBuffer[3], sizeof(tempBuffer[3]), "Humidity: %4.2f %%RH    ", sht30_humidity);
        break;

      case 15:
        strcpy(tempBuffer[0], "PM Levels Overview  ");
        snprintf(tempBuffer[1], sizeof(tempBuffer[1]), "PM1.0: %4d ug/m3    ", pmsData.pm1_0);
        snprintf(tempBuffer[2], sizeof(tempBuffer[2]), "PM2.5: %4d ug/m3    ", pmsData.pm2_5);
        snprintf(tempBuffer[3], sizeof(tempBuffer[3]), "PM10 : %4d ug/m3    ", pmsData.pm10_0);
        break;
      
      case 16:
        strcpy(tempBuffer[0], "Air Qualify Overview");
        snprintf(tempBuffer[1], sizeof(tempBuffer[1]), "CO2:  %4d ppm      ", (int)co2_ppm);
        snprintf(tempBuffer[2], sizeof(tempBuffer[2]), "eCO2: %4d ppm      ", eco2);
        snprintf(tempBuffer[3], sizeof(tempBuffer[3]), "eTVOC:%4d ppb      ", etvoc);
        break;

      // Surprisingly, I didn't find the LCD display mode corresponding to 114514
      default:
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "   What's Up Bro?   ");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "                    ");
        break;
    }
    // Compare the contents of the buffer and update the corresponding line if it has changed
    for (int i = 0; i < 4; i++) {
      if (strcmp(buffer[i], tempBuffer[i]) != 0) {
        lcd.setCursor(0, i); // Set the cursor to line i
        lcd.print(tempBuffer[i]); // Print new content
        strcpy(buffer[i], tempBuffer[i]); // Update the cache
      }
    }
  }

}

// The fan modes are classified according to DISPLAYMODE, Auto: 10, On: 11, Off: 12.
// The corresponding FANMODE is Auto: 0, On: 1, Off: 2.
void FanThread(){
  Fancount--;
  if (Fancount <= 0){
    Fancount = CONSTFANCOUNT;
    switch (DISPLAYMODE){
      case 10:  // Auto
        FANMODE = 0;
        break;
      case 11:  // On
        FANMODE = 1;
        break;
      case 12:  // Off
        FANMODE = 2;
        break;
      default:
        break;
    }
    switch (FANMODE){
      case 0:  // Auto
        digitalWrite(FanPin, LOW); // 风扇打开
        break;
      case 1:  // On
        digitalWrite(FanPin, LOW); // 风扇打开
        break;
      case 2:  // Off
        digitalWrite(FanPin, HIGH); // 风扇关闭
        break;
      default:
        break;
    }
  }
}
