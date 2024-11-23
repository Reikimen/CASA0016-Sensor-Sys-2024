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
      case 1: // 向右：case 2，向左：case 1，按下Encoder case 13
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|TIME| |T&RH| | PM |");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "  <>                ");
        break;

      case 2: // 向右：case 3，向左：case 1，按下Encoder case 14
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|TIME| |T&RH| | PM |");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "         <>         ");
        break;

      case 3:  // 向右：case 6，向左：case 2，按下Encoder case 15
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|TIME| |T&RH| | PM |");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "                <>  ");
        break;

      case 4:  // 向右：case 5，向左：case 1，按下Encoder case 14
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|T&RH| | PM | | CO2|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "  <>                ");
        break;

      case 5:  // 向右：case 6，向左：case 4，按下Encoder case 15
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|T&RH| | PM | | CO2|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "         <>         ");
        break;
      
      case 6:  // 向右：case 9，向左：case 5，按下Encoder case 16
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|T&RH| | PM | | CO2|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "                <>  ");
        break;

      case 7:  // 向右：case 8，向左：case 4，按下Encoder case 15
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "| PM | | CO2| |FANs|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "  <>                ");
        break;

      case 8:  // 向右：case 9，向左：case 7，按下Encoder case 16
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "| PM | | CO2| |FANs|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "         <>         ");
        break;
        
      case 9:  // 向右：case 9，向左：case 8，按下Encoder case 10
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "| PM | | CO2| |FANs|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "                <>  ");
        break;

      // 以下为选择风扇模式 case 10 到 case 12
      // 只要在哪个界面就是什么模式，不需要二次确认，只对左右旋转和按HomeBtn有响应
      case 10:  // 向右：case 11，向左：case 10，
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|AUTO| | ON | | OFF|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "  <>                ");
        break;

      case 11:  // 向右：case 12，向左：case 10，
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|AUTO| | ON | | OFF|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "         <>         ");
        break;

      case 12:  // 向右：case 12，向左：case 11，
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|AUTO| | ON | | OFF|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "                <>  ");
        break;

      // 以下为显示时间、传感器等的模式，只对HomeBtn有响应
      case 13:
        sprintf(tempBuffer[0], "London:%s        ", londonST.c_str());
        sprintf(tempBuffer[1], "%s %s ", londonDate.c_str(), londonTime.c_str());
        sprintf(tempBuffer[2], "China :%s        ", chinaST.c_str());
        sprintf(tempBuffer[3], "%s %s ", chinaDate.c_str(), chinaTime.c_str());
        break;

      case 14:
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|T&RH| |T&RH| |T&RH|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "         <>         ");
        break;

      case 15:
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "| PM | | PM | | PM |");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "                <>  ");
        break;
      
      case 16:
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "|CO2 | |CO2 | | CO2|");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "         <>         ");
        break;

      // 竟然没有找到114514对应的LCD显示模式
      default:
        strcpy(tempBuffer[0], "****** ****** ******");
        strcpy(tempBuffer[1], "   What's Up Bro?   ");
        strcpy(tempBuffer[2], "****** ****** ******");
        strcpy(tempBuffer[3], "                    ");
        break;
    }
    // 比较缓冲区内容，如果有变化，则更新对应的行
    for (int i = 0; i < 4; i++) {
      if (strcmp(buffer[i], tempBuffer[i]) != 0) {
        lcd.setCursor(0, i); // 设置光标到第 i 行
        lcd.print(tempBuffer[i]); // 打印新的内容
        strcpy(buffer[i], tempBuffer[i]); // 更新缓存
      }
    }
  }

}

// 风扇的模式根据DISPLAYMODE分为，Auto：10，On: 11, Off: 12
// 对应的 FANMODE 分别为，Auto：0，On: 1, Off: 2
int FANMODE = 0;

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
