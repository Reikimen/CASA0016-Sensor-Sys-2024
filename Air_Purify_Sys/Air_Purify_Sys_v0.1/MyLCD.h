LiquidCrystal_I2C lcd(0x27, 20, 4);

int LCDcount = 200;

void LCDThread(){
  LCDcount--;
  if (LCDcount <= 0){
    LCDcount = 200;
    switch (DISPLAYMODE){
      // Hello Dankao，这个界面将持续到按下或者转动旋转编码器，并且跳转 case 1
      case 0:
        lcd.setCursor(0, 0);lcd.print("Hello World!  it's ");
        lcd.setCursor(0, 1);lcd.print("   Dankao Kingdom  ");
        lcd.setCursor(0, 2);lcd.print("Press or Rotate The ");
        lcd.setCursor(0, 3);lcd.print("Encoder for Continue");
        break;
      // 
      // Encoder 向右旋转 到底之后不允许往右继续旋转
      // Encoder 向左旋转 到底之后不允许往左继续旋转
      case 1: // 向右：case 2，向左：case 1
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("|TIME| |T&RH| | PM |");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("  <>                ");
        break;

      case 2: // 向右：case 3，向左：case 1
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("|TIME| |T&RH| | PM |");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("         <>         ");
        break;

      case 3:  // 向右：case 6，向左：case 2
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("|TIME| |T&RH| | PM |");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("                <>  ");
        break;

      case 4:  // 向右：case 5，向左：case 1
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("|T&RH| | PM | | CO2|");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("  <>                ");
        break;

      case 5:  // 向右：case 6，向左：case 4
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("|T&RH| | PM | | CO2|");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("         <>         ");
        break;
      
      case 6:  // 向右：case 9，向左：case 5
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("|T&RH| | PM | | CO2|");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("                <>  ");
        break;

      case 7:  // 向右：case 8，向左：case 4
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("| PM | | CO2| |FANs|");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("  <>                ");
        break;

      case 8:  // 向右：case 9，向左：case 7
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("| PM | | CO2| |FANs|");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("         <>         ");
        break;
        
      case 9:  // 向右：case 9，向左：case 8
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("| PM | | CO2| |FANs|");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("                <>  ");
        break;

      // 以下为选择风扇模式 case 10 到 case 12
      case 10:
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("|AUTO| | ON | | OFF|");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("  <>                ");
        break;

      case 11:
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("|AUTO| | ON | | OFF|");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("         <>         ");
        break;

      case 12:
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("|AUTO| | ON | | OFF|");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("                <>  ");
        break;

      // 竟然没有找到对应的LCD显示模式
      default:
        lcd.setCursor(0, 0);lcd.print("****** ****** ******");
        lcd.setCursor(0, 1);lcd.print("   What's Up Bro?   ");
        lcd.setCursor(0, 2);lcd.print("****** ****** ******");
        lcd.setCursor(0, 3);lcd.print("                    ");
        break;
    }
  }

}
