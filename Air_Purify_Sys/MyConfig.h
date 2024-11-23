//////////////////////////////////////////////////////// Threads Time ///////////////////////////////////////////////////////
// Change the values here to modify the frequency for every threads, except the 1kHz threads
/* Wifi */
const int CONSTTIMECOUNT = 1000; 
int timecounter = CONSTTIMECOUNT; // WorldTimerThread

/* Actuator */
const int CONSTLCDCOUNT = 50; 
const int CONSTFANCOUNT = 100; 
int LCDcount = CONSTLCDCOUNT;
int Fancount = CONSTFANCOUNT;

/* Ctrl */
const int CONSTENCODERCOUNT = 10;  // Used to increase the period for detecting the rotary encoder to enable runtime support for modeLogic
int encodercount = CONSTENCODERCOUNT;

/* Sensor */
const int CONSTMQ135COUNT = 2000; 
int MQ135count = CONSTMQ135COUNT;

//////////////////////////////////////////////////////// Wi-Fi ///////////////////////////////////////////////////////
// Wi-Fi 信息
const char* ssid = "Reiki_Desktop";
const char* password = "Reikimen";

// 创建时区对象
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
#define FanPin    2    // D4

/////////////////////////////////////////////////////// Ctrl IO ////////////////////////////////////////////////////////
#define encoderPinA     12    // D6
#define encoderPinB     13    // D7
#define encoderPinBtn   14    // D5
#define homeBtnPin      0     // D3

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
#include "MQ135.h"

MQ135 SensorMQ135 = MQ135(A0); // 传感器接到 A0 引脚

float co2_ppm = 114514;
float rzero = 440;
float rs = 11451;