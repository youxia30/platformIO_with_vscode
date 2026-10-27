//NX3224F024 result is OK,esp32 connect to NX3224F024 directly with pin5 pin16 pin17!
#include <Arduino.h>
#include <Nextion.h>

// 定义 Nextion 显示屏的串口
#define nexSerial Serial2

// 创建 Nextion 组件对象（例如一个按钮和一个文本框）
NexButton b0 = NexButton(0, 2, "b0"); // 页面0，ID为1的按钮
NexText t0 = NexText(0, 1, "t0");    // 页面0，ID为2的文本框

// Nextion 事件列表
NexTouch *nex_listen_list[] = {
    &b0,
    NULL
};

// 按钮事件回调函数
void b0PopCallback(void *ptr) {
  t0.setText("Hello, ESP32!"); // 设置文本框内容
}

void setup() {
  // 初始化串口
  Serial.begin(115200);       // 调试串口
  nexSerial.begin(9600, SERIAL_8N1, 16, 17); // Nextion 串口，GPIO16为RX，GPIO17为TX

  // 注册按钮事件
  b0.attachPop(b0PopCallback, &b0);

  Serial.println("Nextion Example Start");
}

void loop() {
  // 监听 Nextion 事件
  nexLoop(nex_listen_list);
}