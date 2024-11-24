// v0.5
#include "MyConfig.h"
#include "MyWifi.h"
#include "MyActuator.h"
#include "MyCtrlLogic.h" // 我是: 唱跳Rap篮球高手
#include "MySensors.h"

/* 线程任务声明 */
// 用户交互线程
Ritos taskEncoder;
Ritos taskCheckEncoder; 
Ritos taskButton;
Ritos taskHomeButton;
// 执行器线程
Ritos taskLCD;
Ritos taskFan;
// 获取数据的线程
Ritos taskTimer;
// Ritos taskDHT22;
Ritos taskMeasureMQ135;
Ritos taskMeasureCCS881;
Ritos taskMeasurePMS7003;


void setup() {
  // Enable Serial
  Serial.begin(9600);
  Serial.println("Starting...");
  // Enable I2C
  Wire.begin(); 

  /* Initialize Threads for user interaction*/
  // Initialize the pin for encoder
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderPinBtn, INPUT_PULLUP);
  // Initialize the pin for HomeBtn
  pinMode(homeBtnPin, INPUT);

  /* Initialize Threads for actuators*/
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  // Initialize the Pin of the Fan(NMOS)
  pinMode(FanPin, OUTPUT);

  /* Initialize Threads for grabbing datas*/
  // Initilize the sensors
  // dht22.begin();
  InitilizeCCS811();
  // Initilize the WiFi
  InitilizeWiFiNTP();

  /* Create threads */
  // Threads for Interaction
  taskEncoder.task(encoderThread); 
  taskCheckEncoder.task(CheckEncoderThread);
  taskButton.task(buttonThread);
  taskHomeButton.task(homeBtnThread);
  // Threads for Actuators
  taskLCD.task(LCDThread);
  taskFan.task(FanThread);
  // Threads for grab datas
  taskTimer.task(WorldTimerThread);
  // taskDHT22.task(DHT22Thread);
  taskMeasureMQ135.task(MQ135Thread);
  taskMeasureCCS881.task(CCS811Thread);
  taskMeasurePMS7003.task(PMS7003Thread);
}

void loop() {
  // Empty, all logic is executed in the thread
}
