/*
struct_message是接收数据的保存变量，类型是结构体。简单配置一下接收回调函数，打印接收到的数据。
*/
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>


// structure example to receive data
// must match the receiver structure
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    bool d;
} struct_message;

// create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo; // parameter for the peer info

// call back when data is sent
void OnDataRecv(const esp_now_recv_info_t *rx_info, const uint8_t *data, int len) {
    memcpy(&myData, data, sizeof(myData));
    Serial.print("Received: ");
    Serial.println(len);
    Serial.print("char: ");
    Serial.println(myData.a); 
    Serial.print("Int: ");
    Serial.println(myData.b);
    Serial.print("Float: ");
    Serial.println(myData.c);
    Serial.print("Bool: ");
    Serial.println(myData.d);
    Serial.println(" ");
}

void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    Serial.println("ESPNow/Basic/Master Example");
    Serial.print("STA MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("STA CHANNEL ");
    Serial.println(WiFi.channel());

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for receive CB to get the status of Trasnmitted packet
    esp_now_register_recv_cb(OnDataRecv);

    
}

void loop() {

    // receive message via ESP-NOW

    delay(2000);
}