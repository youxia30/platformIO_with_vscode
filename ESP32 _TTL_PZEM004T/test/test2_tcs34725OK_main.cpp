//test2_tcs34725 result is OK,esp32 connect to tcs34725 directly with pin21 pin22!
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#define pin2 2   //gpio pin 2 for led
// Create an instance of the TCS34725 sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(115200);
  //Serial.begin(9600);
  while (!Serial) {
    delay(10); // Wait for Serial to initialize
  }
  Serial.println("TCS34725 Color Sensor Test");

  // Initialize I2C communication the TCS34725 sensor
  if (tcs.begin()) {
    Serial.println("TCS34725 found");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // Halt execution
  }

  // Enable the onboard LED for illumination
  tcs.setInterrupt(false);
  pinMode(pin2, OUTPUT);
}

void loop() {
  uint16_t r, g, b, c;

  // Get raw data from the sensor
  tcs.getRawData(&r, &g, &b, &c);

  // Calculate color temperature and lux
  uint16_t colorTemp = tcs.calculateColorTemperature(r, g, b);
  uint16_t lux = tcs.calculateLux(r, g, b);

  // Print the results
  Serial.print("Red: "); Serial.print(r);
  Serial.print(" Green: "); Serial.print(g);
  Serial.print(" Blue: "); Serial.print(b);
  Serial.print(" Clear: "); Serial.print(c);
  Serial.print(" Color Temp: "); Serial.print(colorTemp);
  Serial.print(" K Lux: "); Serial.println(lux);

  delay(1000); // Wait 1 second before the next reading

  digitalWrite(pin2, HIGH);
  delay(1000);
  digitalWrite(pin2, LOW);
  delay(2000);
}