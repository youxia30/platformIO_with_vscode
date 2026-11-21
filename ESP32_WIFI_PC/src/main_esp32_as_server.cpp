// 服务器负责创建接入点、处理路由并发送数据，客户端负责连接到服务器网络、发送HTTP请求并显示数据
// import required libraries
#include <WiFi.h>
#include <Wire.h>
#include "Grove_Temperature_And_Humidity_Sensor.h"
#include "ESPAsyncWebServer.h"

//#define SSID "ESP32-Server" // 设置 Wi-Fi 名称
#define SSID "ESP32-Access-point" // 设置 Wi-Fi 名称，作为热点
#define PASSWORD "12345678" // 设置 Wi-Fi 密码

#define DHTTYPE DHT20 // DHT20
DHT dht(DHTTYPE); // 初始化 DHT 传感器，不需要定义引脚

// set your access point network credentials
const char* ssid = SSID;
const char* password = PASSWORD;

// create an asyncWebServer object on port 80
AsyncWebServer server(80);
float temp_hum_val[2] = {0.0, 0.0};
char buffer_hum_0[10];
char buffer_hum_1[10];
const char* str1 = "";
const char* str2 = "";

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Web Server");

  // initialize DHT sensor I2C communication, D4 = SDA, D5 = SCL
  Wire.begin(4, 5);
  dht.begin();

  Serial.print("setting AP (access point)... ");

  // connect to Wi-Fi
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(IP);

  // route for root / web page
  server.on("/temperature&humidity", HTTP_GET, [](AsyncWebServerRequest* request) {
    temp_hum_val[0] = dht.readTemperature();
    temp_hum_val[1] = dht.readHumidity();
    sprintf(buffer_hum_0, "%.2f", temp_hum_val[0]);
    sprintf(buffer_hum_1, "%.2f", temp_hum_val[1]);
    str1 = buffer_hum_0;
    str2 = buffer_hum_1;
    String html = "<html><body><h1>ESP32 Web Server</h1><p>Temperature: " + String(str1) + " °C</p><p>Humidity: " + String(str2) + " %</p></body></html>";
    request->send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  if (WiFi.softAPgetStationNum() > 0) {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      temp_hum_val[0] = temperature;
      temp_hum_val[1] = humidity;
      sprintf(buffer_hum_0, "%.2f", temp_hum_val[0]);
      sprintf(buffer_hum_1, "%.2f", temp_hum_val[1]);
      str1 = buffer_hum_0;
      str2 = buffer_hum_1;
      Serial.print("Temperature: ");
      Serial.print(str1);
      Serial.print(" °C, Humidity: ");
      Serial.print(str2);
      Serial.println(" %");
    }
    delay(1000);
  }
}
