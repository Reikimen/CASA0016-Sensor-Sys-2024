#include <Wire.h>
#include "ccs811.h"
#include "PMS.h"  // PMS7003 库

// PMS7003 使用 UART0（GPIO1 和 GPIO3）
PMS pms(Serial);
PMS::DATA pmsData;

// CCS811 初始化（nWAKE 连接到 D8）
CCS811 ccs811(0); // nWAKE 引脚连接到 D3

void setup() {
  // 启用串口和 I2C
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial1.println("Starting sensor setup...");

  // 初始化 CCS811
  Wire.begin(); // 初始化 I2C
  bool ok = ccs811.begin();
  if (!ok) {
    Serial1.println("CCS811 initialization failed!");
  }

  // 初始化 PMS7003
  // Print CCS811 versions
  Serial1.print("setup: hardware    version: "); Serial1.println(ccs811.hardware_version(),HEX);
  Serial1.print("setup: bootloader  version: "); Serial1.println(ccs811.bootloader_version(),HEX);
  Serial1.print("setup: application version: "); Serial1.println(ccs811.application_version(),HEX);
  
  // Start measuring
  ok= ccs811.start(CCS811_MODE_1SEC);
  if( !ok ) Serial1.println("setup: CCS811 start FAILED");

  Serial1.begin(9600);  // 设置 UART1
  delay(3000);  // 等待 PMS7003 启动

  Serial1.println("Sensors initialized successfully.");
}

void loop() {
  // 读取 PMS7003 数据
  if (pms.read(pmsData)) {
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(pmsData.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(pmsData.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(pmsData.PM_AE_UG_10_0);
  } else {
    Serial.println("Error reading PMS7003 data");
  }

  // 读取 CCS811 数据
  uint16_t eco2, etvoc, errstat, raw;
  ccs811.read(&eco2, &etvoc, &errstat, &raw);

  if (errstat == CCS811_ERRSTAT_OK) {
    Serial1.print("CCS811: ");
    Serial1.print("eco2=");  Serial1.print(eco2);     Serial1.print(" ppm  ");
    Serial1.print("etvoc="); Serial1.print(etvoc);    Serial1.print(" ppb  ");
    Serial1.println();
  } else if (errstat == CCS811_ERRSTAT_OK_NODATA) {
    Serial1.println("CCS811: Waiting for new data...");
  } else if (errstat & CCS811_ERRSTAT_I2CFAIL) {
    Serial1.println("CCS811: I2C error");
  } else {
    Serial1.print("CCS811: errstat="); 
    Serial1.print(errstat, HEX); 
    Serial1.print("="); 
    Serial1.println(ccs811.errstat_str(errstat));
  }

  // 每次循环等待一段时间
  delay(10000);
}
