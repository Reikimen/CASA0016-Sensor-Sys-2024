#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ezTime.h>
#include <LiquidCrystal_I2C.h>
#include "MQ135.h"
#include "ccs811.h"  // CCS811 library
// #include "PMS.h" // Don't need it anymore, for the fuctions insides has delay or sleep that would block the whole sys
#include "ritos.h" // https://github.com/0ingchun/RITOS-lib-Arduino

//////////////////////////////////////////////////////// Threads Time ///////////////////////////////////////////////////////
// Change the values here to modify the frequency for every threads, except the 1kHz threads
/* Wifi */
const int CONSTTIMECOUNT = 1000; 
int timecounter = CONSTTIMECOUNT; // WorldTimerThread

/* Actuator */
const int CONSTLCDCOUNT = 50; 
const int CONSTFANCOUNT = 50; 
int LCDcount = CONSTLCDCOUNT;
int Fancount = CONSTFANCOUNT;

/* Ctrl */
const int CONSTENCODERCOUNT = 10;  // Used to increase the period for detecting the rotary encoder to enable runtime support for modeLogic
int encodercount = CONSTENCODERCOUNT;

/* Sensor */
const int CONSTMQ135COUNT = 2000; 
int MQ135count = CONSTMQ135COUNT;

const int CONSTPMS7003COUNT = 10000;
int PMS7003count = CONSTPMS7003COUNT;

const int CONSTSHT30COUNT = 2000;
int sht30count = CONSTSHT30COUNT;

//////////////////////////////////////////////////////// Wi-Fi ///////////////////////////////////////////////////////
// Wi-Fi info
// inside secrets.h

// Create a time zone object
Timezone londonTZ;
Timezone chinaTZ;

String londonST;
String londonDate;
String londonTime;
String chinaST;
String chinaDate;
String chinaTime;

//////////////////////////////////////////////////////// Actuator ///////////////////////////////////////////////////////
// LCD2004
LiquidCrystal_I2C lcd(0x27, 20, 4); // VDD to 5V, GND to GND, SDA to D2, SCL to D1

int DISPLAYMODE = 0;

char buffer[4][21]; // 4 lines of up to 20 characters each for storage of the current display

// Fan & NMOS
// #define FanPin    2    // D4
#define FanPin    16    // D0

// The fan modes are classified according to DISPLAYMODE, Auto: 10, On: 11, Off: 12.
// The corresponding FANMODE is Auto: 0, On: 1, Off: 2.
int FANMODE = 0;

/////////////////////////////////////////////////////// Ctrl IO ////////////////////////////////////////////////////////
#define encoderPinA     12    // D6
#define encoderPinB     13    // D7
#define encoderPinBtn   14    // D5
#define homeBtnPin      15    // D8

// De-jitter time
#define DEBOUNCE_TIME 30  // Used for both encoderBtn (Simplified as 'Button') and homeBtn
unsigned long ButtonlastDebounceTime = 0;
unsigned long homeBtnlastDebounceTime = 0;

// Save rotation count, button press state
volatile int encoderPosition = 0;
volatile bool buttonPressed = false;
volatile bool homebuttonPressed = false;

// The state of encoder pins, use HIGH to avoid the first detceting turn
int lastEncoderStateA = HIGH;
int lastEncoderStateB = HIGH;

// Counterclockwise (left) is 1, Clockwise (right) is 0, default is 11451
int EncoderRotate = 11451;

// Button status, default null pin high
int lastButtonState = HIGH;
int homelastButtonState = HIGH;

/////////////////////////////////////////////////////// Sensors ////////////////////////////////////////////////////////
// MQ135

MQ135 SensorMQ135 = MQ135(A0); // Sensor connected to pin A0

float co2_ppm = 114514;
float rzero = 440;
float rs = 11451;

// ccs811
// Wiring for ESP8266 NodeMCU boards: VDD to 3V3, GND to GND, SDA to D2, SCL to D1, nWAKE to D3 (or GND)
CCS811 ccs811(0); // nWAKE on D3

const int CONSTCCS811COUNT = 1000;
int ccs811count = CONSTCCS811COUNT;

uint16_t eco2, etvoc, errstat, raw;

// PMS7003
#define FRAME_LENGTH 32  // PMS7003 data frame length
#define FRAME_START_1 0x42
#define FRAME_START_2 0x4D

uint8_t pmsbuffer[FRAME_LENGTH];  // Data buffer
uint8_t bufferIndex = 0;          // Buffer index
bool frameReady = false;          // Flag bit indicating if a full frame is available

struct PMSData {
  uint16_t pm1_0;
  uint16_t pm2_5;
  uint16_t pm10_0;
};

PMSData pmsData;

// SHT30传感器的I2C地址
#define Addr_SHT30 0x44

// 存储SHT30测量数据的变量
uint8_t sht30_data[6];
float sht30_cTemp;     // 摄氏温度
float sht30_fTemp;     // 华氏温度
float sht30_humidity;  // 相对湿度
