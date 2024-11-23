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
// Wiring for ESP8266 NodeMCU boards: VDD to 3V3, GND to GND, SDA to D2, SCL to D1, nWAKE to D3 (or GND)
CCS811 ccs811(0); // nWAKE on D3

const int CONSTCCS811COUNT = 1000;
int ccs811count = CONSTCCS811COUNT;

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

uint16_t eco2, etvoc, errstat, raw;

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




