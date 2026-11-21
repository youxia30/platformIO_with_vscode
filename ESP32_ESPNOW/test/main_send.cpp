/*
struct_message是发送数据的保存变量，类型是结构体。先在setup()中设置wifi工作在STA模式，然后调用esp_now_init()初始化。
将配对的设备信息进行添加，简单配置一下发送回调函数，打印是否发送成功。主函数中，每2秒发送一次数据。
esp_now_send返回是否发送出去，回调函数中展示是否成功发送给接收方。
*/
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// replace with your receiver's MAC address
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xA1, 0xB2, 0xC3};

// structure example to send data
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
void OnDataSent(const esp_now_send_info_t *tx_info, esp_now_send_status_t status) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
             tx_info->des_addr[0], tx_info->des_addr[1], tx_info->des_addr[2],
             tx_info->des_addr[3], tx_info->des_addr[4], tx_info->des_addr[5]);
    Serial.print("Last Packet Sent to: ");
    Serial.println(macStr);
    Serial.print("Last Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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

    // Once ESPNow is successfully Init, we will register for Send CB to get the status of Trasnmitted packet
    esp_now_register_send_cb(OnDataSent);

    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop() {
    // set values to send
    strcpy(myData.a, "this is a char");
    myData.b = random(1, 20);
    myData.c = 1.2;
    myData.d = false;

    // send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

    if (result == ESP_OK) {
        Serial.println("send with success!");
    } else {
        Serial.println("send data with error!");
    }
    delay(2000);
}