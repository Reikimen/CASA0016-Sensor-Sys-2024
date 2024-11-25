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
// General Gas Concentration Calculation Function for MQ135
float calculateGasConcentration(float rs, float rzero, float a, float b) {
  float ratio = rs / rzero; // Calculate the Rs/R0 ratio
  return a * pow(ratio, b); // Calculate the concentration using the formula
}
void MQ135Thread(){
  MQ135count--;
  if (MQ135count <= 0){
    MQ135count = CONSTMQ135COUNT;

    rzero = SensorMQ135.getRZero();     // Get the reference value in the air R₀
    rs = SensorMQ135.getResistance();   // Get sensor instantaneous resistance Rs

    // CO2 concentration (PPM)
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
// Non-blocking read of PMS7003 data
void readPMS7003() {
  while (Serial.available()) {
    uint8_t byte = Serial.read();

    // If the buffer index is 0 and the first byte of the frame header is received
    if (bufferIndex == 0 && byte == FRAME_START_1) {
      pmsbuffer[bufferIndex++] = byte;
    }
    // If the buffer index is 1 and the second byte of the frame header is received
    else if (bufferIndex == 1 && byte == FRAME_START_2) {
      pmsbuffer[bufferIndex++] = byte;
    }
    // If frame data is being received
    else if (bufferIndex > 1 && bufferIndex < FRAME_LENGTH) {
      pmsbuffer[bufferIndex++] = byte;
      // When a full frame is received
      if (bufferIndex == FRAME_LENGTH) {
        bufferIndex = 0;
        frameReady = true;
        break;
      }
    }
    // Reset buffer if received data does not match header
    else {
      bufferIndex = 0;
    }
  }
}

// Parsing PMS7003 data frames
bool parsePMS7003(const uint8_t* frame, PMSData& data) {
  // Check the frame header
  if (frame[0] != FRAME_START_1 || frame[1] != FRAME_START_2) {
    return false;
  }

  // Check frame checksum
  uint16_t checksum = 0;
  for (int i = 0; i < FRAME_LENGTH - 2; i++) {
    checksum += frame[i];
  }
  uint16_t receivedChecksum = (frame[FRAME_LENGTH - 2] << 8) | frame[FRAME_LENGTH - 1];
  if (checksum != receivedChecksum) {
    return false;
  }

  // Parsing PM data
  data.pm1_0 = (frame[10] << 8) | frame[11];
  data.pm2_5 = (frame[12] << 8) | frame[13];
  data.pm10_0 = (frame[14] << 8) | frame[15];

  return true;
}

void PMS7003Thread(){
  PMS7003count--;
  if (PMS7003count <= 0){
    PMS7003count = CONSTPMS7003COUNT;

    // Non-blocking read of PMS7003 data
    readPMS7003();
    // If there is a full frame, parse and output
    if (frameReady) {
      frameReady = false;
      if (parsePMS7003(pmsbuffer, pmsData)) { // Parsing PMS7003 data frames
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


