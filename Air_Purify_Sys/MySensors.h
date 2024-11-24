// Nothing Now

// #include <DHT.h>

// // 定义 DHT 类型和引脚
// #define DHTPIN 2 // 使用 GPIO2 D4
// #define DHTTYPE DHT22 // DHT22 类型

// DHT dht22(DHTPIN, DHTTYPE);

// int DHT22count = 1000;

// void DHT22Thread() {
//   DHT22count--;
//   if (DHT22count <= 0){
//     DHT22count = 1000;
//     // 读取湿度和温度
//   float temp = dht22.readTemperature();
//   float hum = dht22.readHumidity();
//   if (!isnan(temp) && !isnan(hum)) {
//     Serial.print("温度: "); Serial.println(temp);
//     Serial.print("湿度: "); Serial.println(hum);
//   } else {
//     Serial.println("读取失败！");
//   }
//   }

// }

// MQ135
// 通用气体浓度计算函数 for MQ135
float calculateGasConcentration(float rs, float rzero, float a, float b) {
  float ratio = rs / rzero; // 计算 Rs/R0 的比例
  return a * pow(ratio, b); // 使用公式计算浓度
}
void MQ135Thread(){
  MQ135count--;
  if (MQ135count <= 0){
    MQ135count = CONSTMQ135COUNT;

    rzero = SensorMQ135.getRZero();     // 获取空气中的基准值 R₀
    rs = SensorMQ135.getResistance();  // 获取传感器瞬时电阻 Rs

    // CO2 浓度 (PPM)
    co2_ppm = calculateGasConcentration(rs, rzero, 110.47, -2.62);
    Serial.print("CO2 (ppm): ");
    Serial.println(co2_ppm);
  }
}

// ccs811

void InitilizeCCS811(){
  // Enable CCS811
  ccs811.set_i2cdelay(50); // Needed for ESP8266 because it doesn't handle I2C clock stretch correctly
  bool ok= ccs811.begin();
  if( !ok ) Serial.println("setup: CCS811 begin FAILED");

  // Print CCS811 versions
  Serial.print("setup: hardware    version: "); Serial.println(ccs811.hardware_version(),HEX);
  Serial.print("setup: bootloader  version: "); Serial.println(ccs811.bootloader_version(),HEX);
  Serial.print("setup: application version: "); Serial.println(ccs811.application_version(),HEX);
  
  // Start measuring
  ok= ccs811.start(CCS811_MODE_1SEC);
  if( !ok ) Serial.println("setup: CCS811 start FAILED");
}

void CCS811Thread(){
  ccs811count--;
  if (ccs811count <= 0){
    ccs811count = CONSTCCS811COUNT;

    ccs811.read(&eco2,&etvoc,&errstat,&raw); 
    // Print measurement results based on status
    if( errstat==CCS811_ERRSTAT_OK ) { 
      Serial.print("CCS811: ");
      Serial.print("eco2=");  Serial.print(eco2);     Serial.print(" ppm  ");
      Serial.print("etvoc="); Serial.print(etvoc);    Serial.print(" ppb  ");
      //Serial.print("raw6=");  Serial.print(raw/1024); Serial.print(" uA  "); 
      //Serial.print("raw10="); Serial.print(raw%1024); Serial.print(" ADC  ");
      //Serial.print("R="); Serial.print((1650*1000L/1023)*(raw%1024)/(raw/1024)); Serial.print(" ohm");
      Serial.println();
    } else if( errstat==CCS811_ERRSTAT_OK_NODATA ) {
      Serial.println("CCS811: waiting for (new) data"); 
    } else if( errstat & CCS811_ERRSTAT_I2CFAIL ) { 
      Serial.println("CCS811: I2C error");
    } else {
      Serial.print("CCS811: errstat="); Serial.print(errstat,HEX); 
      Serial.print("="); Serial.println( ccs811.errstat_str(errstat) ); 
    }

  }
}

// SHT30

// PMS7003
// 非阻塞读取PMS7003数据
void readPMS7003() {
  while (Serial.available()) {
    uint8_t byte = Serial.read();

    // 如果缓冲区索引为0且接收到帧头第一个字节
    if (bufferIndex == 0 && byte == FRAME_START_1) {
      pmsbuffer[bufferIndex++] = byte;
    }
    // 如果缓冲区索引为1且接收到帧头第二个字节
    else if (bufferIndex == 1 && byte == FRAME_START_2) {
      pmsbuffer[bufferIndex++] = byte;
    }
    // 如果正在接收帧数据
    else if (bufferIndex > 1 && bufferIndex < FRAME_LENGTH) {
      pmsbuffer[bufferIndex++] = byte;
      // 当接收到完整帧时
      if (bufferIndex == FRAME_LENGTH) {
        bufferIndex = 0;
        frameReady = true;
        break;
      }
    }
    // 如果接收到的数据不符合帧头，重置缓冲区
    else {
      bufferIndex = 0;
    }
  }
}

// 解析PMS7003数据帧
bool parsePMS7003(const uint8_t* frame, PMSData& data) {
  // 检查帧头
  if (frame[0] != FRAME_START_1 || frame[1] != FRAME_START_2) {
    return false;
  }

  // 检查帧校验和
  uint16_t checksum = 0;
  for (int i = 0; i < FRAME_LENGTH - 2; i++) {
    checksum += frame[i];
  }
  uint16_t receivedChecksum = (frame[FRAME_LENGTH - 2] << 8) | frame[FRAME_LENGTH - 1];
  if (checksum != receivedChecksum) {
    return false;
  }

  // 解析PM数据
  data.pm1_0 = (frame[10] << 8) | frame[11];
  data.pm2_5 = (frame[12] << 8) | frame[13];
  data.pm10_0 = (frame[14] << 8) | frame[15];

  return true;
}

void PMS7003Thread(){
  PMS7003count--;
  if (PMS7003count <= 0){
    PMS7003count = CONSTPMS7003COUNT;

    // 非阻塞读取PMS7003数据
    readPMS7003();
    // 如果有完整帧，解析并输出
    if (frameReady) {
      frameReady = false;
      if (parsePMS7003(pmsbuffer, pmsData)) { // 解析PMS7003数据帧
        Serial.print("PM 1.0 (ug/m3): ");
        Serial.println(pmsData.pm1_0);
        Serial.print("PM 2.5 (ug/m3): ");
        Serial.println(pmsData.pm2_5);
        Serial.print("PM 10.0 (ug/m3): ");
        Serial.println(pmsData.pm10_0);
        Serial.println();
      } else {
        Serial.println("Invalid frame");
      }
    }
  }
}


