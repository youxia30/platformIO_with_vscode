#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <WiFi.h>
#include <time.h>

// 定义 SD 卡的 CS 引脚
#define SD_CS 5

// WiFi 配置
const char* ssid = "NKSC-2.4G";       // 替换为您的 WiFi 名称
const char* password = "zs62psv701ym2"; // 替换为您的 WiFi 密码

// NTP 服务器配置
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 8 * 3600; // GMT+8 时区
const int daylightOffset_sec = 0;

void setup() {
  // 初始化串口
  Serial.begin(115200);

  // 连接 WiFi
  Serial.printf("连接到 WiFi: %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi 已连接");

  // 初始化时间
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("正在同步时间...");
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("无法获取时间");
    return;
  }
  Serial.println("时间同步成功");

  // 初始化 SD 卡
  if (!SD.begin(SD_CS)) {
    Serial.println("SD 卡初始化失败！");
    return;
  }
  Serial.println("SD 卡初始化成功！");

  // 获取当前时间
  char timeStr[64];
  strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeinfo);
  Serial.printf("当前时间: %s\n", timeStr);

  // 写入时间到 SD 卡
  writeTimeToSD("/time_log.txt", timeStr);
}

void loop() {
  // 空循环
}

// 写入时间到 SD 卡
void writeTimeToSD(const char* path, const char* timeStr) {
  Serial.printf("写入时间到文件: %s\n", path);

  File file = SD.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("无法打开文件");
    return;
  }
  if (file.println(timeStr)) {
    Serial.println("时间写入成功");
  } else {
    Serial.println("时间写入失败");
  }
  file.close();
}