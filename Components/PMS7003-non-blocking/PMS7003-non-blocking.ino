#include <Arduino.h>

#define FRAME_LENGTH 32  // PMS7003数据帧长度
#define FRAME_START_1 0x42
#define FRAME_START_2 0x4D

uint8_t buffer[FRAME_LENGTH];  // 数据缓冲区
uint8_t bufferIndex = 0;       // 缓冲区索引
bool frameReady = false;       // 标志位，表示是否有完整帧可用

struct PMSData {
  uint16_t pm1_0;
  uint16_t pm2_5;
  uint16_t pm10_0;
};

PMSData pmsData;

void setup() {
  Serial.begin(9600);  // PMS7003的串口通信
  Serial.println("Starting...");
}

void loop() {
  // 非阻塞读取PMS7003数据
  readPMS7003();

  // 如果有完整帧，解析并输出
  if (frameReady) {
    frameReady = false;
    if (parsePMS7003(buffer, pmsData)) {
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

  // 其他任务代码可以在这里运行
  delay(10000);
}

// 非阻塞读取PMS7003数据
void readPMS7003() {
  while (Serial.available()) {
    uint8_t byte = Serial.read();

    // 如果缓冲区索引为0且接收到帧头第一个字节
    if (bufferIndex == 0 && byte == FRAME_START_1) {
      buffer[bufferIndex++] = byte;
    }
    // 如果缓冲区索引为1且接收到帧头第二个字节
    else if (bufferIndex == 1 && byte == FRAME_START_2) {
      buffer[bufferIndex++] = byte;
    }
    // 如果正在接收帧数据
    else if (bufferIndex > 1 && bufferIndex < FRAME_LENGTH) {
      buffer[bufferIndex++] = byte;
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
