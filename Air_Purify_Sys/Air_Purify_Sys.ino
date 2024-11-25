// v0.6
#include "MyConfig.h"
#include "MyWifi.h"
#include "MyActuator.h"
#include "MyCtrlLogic.h" // I'm talented at: "唱跳Rap篮球"
#include "MySensors.h"

/* Thread task declaration */
// User Interaction Threads
Ritos taskEncoder;
Ritos taskCheckEncoder; 
Ritos taskButton;
Ritos taskHomeButton;
// Actuator threads
Ritos taskLCD;
Ritos taskFan;
// Threads that fetch data
Ritos taskTimer;
// Ritos taskDHT22;
Ritos taskMeasureMQ135;
Ritos taskMeasureCCS881;
Ritos taskMeasurePMS7003;
Ritos taskMeasureSHT30;


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
  taskMeasureSHT30.task(SHT30Thread);
}

void loop() {
  // Empty, all logic is executed in the thread
}
