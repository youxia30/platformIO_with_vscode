
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#define pin2 2   //gpio pin 2 for led
#define chNum 4  //number of channels
// Define the I2C multiplexer address
#define TCA9548A_ADDRESS 0x70

// Create an instance of the TCS34725 sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_4X);

// Function to select a specific channel on the TCA9548A
void selectTCAChannel(uint8_t channel) {
  //if (channel > 7) return; // TCA9548A has 8 channels (0-7)
  if (channel > chNum) return; // TCA9548A has 8 channels (0-7)
  Wire.beginTransmission(TCA9548A_ADDRESS);
  Wire.write(1 << channel); // Select the channel
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  //Serial.begin(9600);
  while (!Serial) {
    delay(10); // Wait for Serial to initialize
  }
  Serial.println("TCA9548A with TCS34725 Test");

  // Initialize I2C communication
  Wire.begin();

  // Loop through all TCA9548A channels to initialize sensors
  //for (uint8_t i = 0; i < 8; i++) {
  for (uint8_t i = 0; i < chNum; i++) {
    selectTCAChannel(i);
    if (tcs.begin()) {
      Serial.print("TCS34725 found on channel ");
      Serial.println(i);
    } else {
      Serial.print("No TCS34725 found on channel ");
      Serial.println(i);
    }
  }

  // Enable the onboard LED for illumination
  tcs.setInterrupt(false);
  pinMode(pin2, OUTPUT);
}

void loop() {
  uint16_t r, g, b, c;

    // Loop through all TCA9548A channels to read data from sensors
    //for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t i = 0; i < chNum; i++) {
      selectTCAChannel(i);
  
      // Check if the sensor is initialized
      if (!tcs.begin()) {
        Serial.print("No TCS34725 on channel ");
        Serial.println(i);
        continue;
      }
  
      // Get raw data from the sensor
      tcs.getRawData(&r, &g, &b, &c);

      // Calculate color temperature and lux
      uint16_t colorTemp = tcs.calculateColorTemperature(r, g, b);
      uint16_t lux = tcs.calculateLux(r, g, b);

      // Print the results
      Serial.print("Channel "); Serial.print(i);
      Serial.print(" Red: "); Serial.print(r);
      Serial.print(" Green: "); Serial.print(g);
      Serial.print(" Blue: "); Serial.print(b);
      Serial.print(" Clear: "); Serial.print(c);
      Serial.print(" Color Temp: "); Serial.print(colorTemp);
      Serial.print(" K Lux: "); Serial.println(lux);

      delay(1000); // Wait 1 second before the next reading

      digitalWrite(pin2, HIGH);
      delay(1000);
      digitalWrite(pin2, LOW);
      delay(1000);
    }
}