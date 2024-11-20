#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);


void setup(){

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);lcd.print("Hello Dankao!");
  lcd.setCursor(0, 1);lcd.print("Only serve in");
  lcd.setCursor(0, 2);lcd.print("  Dankao Kingdom");
  lcd.setCursor(0, 3);lcd.print("");

}

void loop()

{
  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("|TIME| |T&RH| | PM |");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("  <>                ");
  delay(1500);

  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("|TIME| |T&RH| | PM |");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("         <>         ");
  delay(1500);

  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("|TIME| |T&RH| | PM |");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("                <>  ");
  delay(1500);

  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("|T&RH| | PM | | CO2|");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("                <>  ");
  delay(1500);

  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("| PM | | CO2| |FANs|");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("                <>  ");
  delay(1500);

  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("| PM | | CO2| |FANs|");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("         <>         ");
  delay(1500);

  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("| PM | | CO2| |FANs|");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("  <>                ");
  delay(1500);

  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("|T&RH| | PM | | CO2|");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("  <>                ");
  delay(1500);

  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("|TIME| |T&RH| | PM |");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("  <>                ");
  delay(1500);

  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("|AUTO| | ON | | OFF|");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("  <>                ");
  delay(1500);

  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("|AUTO| | ON | | OFF|");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("         <>         ");
  delay(1500);

  lcd.setCursor(0, 0);lcd.print("****** ****** ******");
  lcd.setCursor(0, 1);lcd.print("|AUTO| | ON | | OFF|");
  lcd.setCursor(0, 2);lcd.print("****** ****** ******");
  lcd.setCursor(0, 3);lcd.print("                <>  ");
  delay(1500);
}