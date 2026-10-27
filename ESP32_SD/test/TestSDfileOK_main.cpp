#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

// 定义 SD 卡的 CS 引脚
#define SD_CS 5
#define pin2 2   //gpio pin 2 for led

void setup() {
  // 初始化串口
  Serial.begin(115200);
  // 初始化 pin2为输出端口
  pinMode(pin2, OUTPUT);

  // 初始化 SD 卡
  if (!SD.begin(SD_CS)) {
    Serial.println("SD 卡初始化失败！");
    return;
  }
  Serial.println("SD 卡初始化成功！");

  // 打开文件进行写入
  File file = SD.open("/data.txt", FILE_WRITE);
  if (file) {
    file.println("Hello, ESP32!"); // 写入数据
    file.close();                 // 关闭文件
    Serial.println("数据写入成功！");
  } else {
    Serial.println("无法打开文件！");
  }
}

void loop() {
  // 空循环
  digitalWrite(pin2, HIGH);
  delay(1000);
  digitalWrite(pin2, LOW);
  delay(1000);

}