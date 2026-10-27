//test PZEM004Tv30 out energy result is ok!

#include <Arduino.h>
#include <PZEM004Tv30.h>

// Define the pins for the hardware serial connection
#define RX_PIN 16 // GPIO16 for RX
#define TX_PIN 17 // GPIO17 for TX

// Create a PZEM object using the defined pins
HardwareSerial PZEMSerial(1); // Use Serial1
PZEM004Tv30 pzem(&PZEMSerial, RX_PIN, TX_PIN);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // Wait for Serial to initialize
  }
  Serial.println("PZEM-004T Test");

  // Initialize the PZEM-004T
  if (!pzem.setAddress(0x01)) { // Set the PZEM address (default is 0x01)
    Serial.println("Failed to set PZEM address!");
  }
}

void loop() {
  // Read voltage
  float voltage = pzem.voltage();
  if (voltage == NAN) {
    Serial.println("Error reading voltage");
  } else {
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");
  }

  // Read current
  float current = pzem.current();
  if (current == NAN) {
    Serial.println("Error reading current");
  } else {
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println(" A");
  }

  // Read power
  float power = pzem.power();
  if (power == NAN) {
    Serial.println("Error reading power");
  } else {
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println(" W");
  }

  // Read energy
  float energy = pzem.energy();
  if (energy == NAN) {
    Serial.println("Error reading energy");
  } else {
    Serial.print("Energy: ");
    Serial.print(energy);
    Serial.println(" kWh");
  }

  // Read frequency
  float frequency = pzem.frequency();
  if (frequency == NAN) {
    Serial.println("Error reading frequency");
  } else {
    Serial.print("frequency: ");
    Serial.print(frequency);
    Serial.println(" hz");
  }

  // Read pf
  float pf = pzem.pf();
  if (pf == NAN) {
    Serial.println("Error reading pf");
  } else {
    Serial.print("pf: ");
    Serial.print(pf);
    Serial.println(" ");
  }
  // Wait 1 second before the next reading
  delay(2000);
}