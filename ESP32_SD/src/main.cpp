// test ESP32 connect to SD card and write a file
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

// 定义 SD 卡的 CS 引脚
#define SD_CS 5
#define pin2 2   //gpio pin 2 for led
#define pin27 27   //gpio pin 27 for button start

static int process = 0; // 进程
static int Int_Counts = 0; // 初始化计数器
static float float_Counts = 0; // 初始化计数器
char Str_counts[64] ;// 用于存储计数器值的字符串
// char countsStr[64]; // 用于存储计数器值的字符串
// char timeStr[64];  // 用于存储时间字符串

void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
void createFile(fs::FS &fs, const char *path, const char *message);
void appendFile(fs::FS &fs, const char *path, const char *message);
void readFile(fs::FS &fs, const char *path);
void deleteFile(fs::FS &fs, const char *path);

void setup() {
  // 初始化串口
  Serial.begin(115200);
  // 初始化 pin2为输出端口
  pinMode(pin2, OUTPUT);  // 设置 pin2 为输出
  pinMode(pin27, INPUT_PULLUP); // 设置 pin27 为输入并启用上拉电阻

  // 初始化 SD 卡
  if (!SD.begin(SD_CS)) {
    Serial.println("SD 卡初始化失败！");
    return;
  }
  Serial.println("SD 卡初始化成功！");

  // 列出根目录内容
  listDir(SD, "/", 0);

  // 创建文件并写入内容
  createFile(SD, "/example.txt", "Hello, ESP32 SD Card!\n");

  // 追加内容到文件
  appendFile(SD, "/example.txt", "This is an appended line.\n");

  // 读取文件内容
  readFile(SD, "/example.txt");

  // 删除文件
  // deleteFile(SD, "/example.txt");

  // 再次列出目录内容
  listDir(SD, "/", 0);
}

void loop() {
  // 空循环
  digitalWrite(pin2, HIGH);
  delay(1000);
  digitalWrite(pin2, LOW);
  delay(1000);
  if (process==0) {
    // 列出根目录内容
    listDir(SD, "/", 0);
    // 创建文件并写入内容
    createFile(SD, "/data.csv", "Hello, ESP32 SD Card!\n");
    // 追加内容到文件
    appendFile(SD, "/data.csv", "This is an data test file.\n");
    // 读取文件内容
    readFile(SD, "/data.csv");
    // 删除文件
    // deleteFile(SD, "/data.csv");
    // 再次列出目录内容
    listDir(SD, "/", 0);
    process=1;
    }
 if (digitalRead(pin27) == LOW) { // 检测到按钮按下
    Int_Counts = (Int_Counts+1);  // TEST Different value
    float_Counts = (float_Counts+2.131452);  // TEST Different value
    String Str1_counts= String(Int_Counts); // 将计数器转换为字符串
    String Str2_counts= String(float_Counts,6); // 将计数器转换为字符串，保留6位小数
     // 打开文件进行写入
    File file = SD.open("/data.csv", FILE_APPEND);
    if (file) {
    //  file.println("Hello, ESP32!"); // 写入数据
      file.println(Str2_counts); // 写入数据
      file.close();                 // 关闭文件
      Serial.println("数据写入成功！");
    } else {
      Serial.println("无法打开文件！");
    }
    // Serial.println(Str1_counts); // 打印计数器值
    Serial.println("按钮被按下，文件计数写入完成！");
    Serial.println("当前数据值Str2："+Str2_counts); // 打印计数器值
  }
  delay(100); // 防抖延时

}

// 列出目录内容
void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("列出目录: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("无法打开目录");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("不是目录");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.printf("  目录: %s\n", file.name());
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      Serial.printf("  文件: %s  大小: %d 字节\n", file.name(), file.size());
    }
    file = root.openNextFile();
  }
}

// 创建文件并写入内容
void createFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("创建文件: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("无法创建文件");
    return;
  }
  if (file.print(message)) {
    Serial.println("文件写入成功");
  } else {
    Serial.println("文件写入失败");
  }
  file.close();
}

// 追加内容到文件
void appendFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("追加内容到文件: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("无法打开文件");
    return;
  }
  if (file.print(message)) {
    Serial.println("内容追加成功");
  } else {
    Serial.println("内容追加失败");
  }
  file.close();
}

// 读取文件内容
void readFile(fs::FS &fs, const char *path) {
  Serial.printf("读取文件: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("无法打开文件");
    return;
  }

  Serial.println("文件内容:");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

// 删除文件
void deleteFile(fs::FS &fs, const char *path) {
  Serial.printf("删除文件: %s\n", path);

  if (fs.remove(path)) {
    Serial.println("文件删除成功");
  } else {
    Serial.println("文件删除失败");
  }
}
