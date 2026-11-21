#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "*WI-Fi Name*";
const char* password = "Wi-Fi Passswd";

const char* laptopIP   = "*Your Laptop IP*"; 
const int   laptopPort = 4210; //Keep it same

WiFiUDP udp;

// buttons
const int btnH = 18;
const int btnJ = 17;
const int btnK = 4;
const int btnL = 21;

// joyslltick
const int joyX = 34;
const int joyY = 35;

const int DZ = 900;   // deadzone

void sendMsg(const char* msg) {
  udp.beginPacket(laptopIP, laptopPort);
  udp.print(msg);
  udp.endPacket();
  Serial.println(msg);
}

void setup() {
  Serial.begin(115200);

  pinMode(btnH, INPUT_PULLUP);
  pinMode(btnJ, INPUT_PULLUP);
  pinMode(btnK, INPUT_PULLUP);
  pinMode(btnL, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(200);

  udp.begin(4211);
}

String lastState = "CENTER";

String getJoyState() {
  int x = analogRead(joyX);
  int y = analogRead(joyY);

  int xs = 0;
  int ys = 0;

  if (x < (2048 - DZ)) xs = -1;
  else if (x > (2048 + DZ)) xs = 1;

  if (y < (2048 - DZ)) ys = 1;       // up
  else if (y > (2048 + DZ)) ys = -1; // down

  if (xs == 0 && ys == 0) return "CENTER";

  if (ys == 1 && xs == -1) return "WA";
  if (ys == 1 && xs ==  1) return "WD";
  if (ys == -1 && xs == -1) return "SA";
  if (ys == -1 && xs ==  1) return "SD";

  if (ys == 1) return "W";
  if (ys == -1) return "S";
  if (xs == -1) return "A";
  if (xs == 1) return "D";

  return "CENTER";
}

void loop() {
  if (digitalRead(btnH) == LOW) sendMsg("H");
  if (digitalRead(btnJ) == LOW) sendMsg("J");
  if (digitalRead(btnK) == LOW) sendMsg("K");
  if (digitalRead(btnL) == LOW) sendMsg("L");

  String js = getJoyState();

  if (js != lastState) {
    sendMsg(js.c_str());
    lastState = js;
  }

  delay(30);
}