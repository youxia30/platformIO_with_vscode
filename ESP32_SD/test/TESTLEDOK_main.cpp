#include <Arduino.h>
#define pin2 2   //gpio pin 2 for led
// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  pinMode(pin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin2, HIGH);
  Serial.println("led>>on");
  delay(1000);
  digitalWrite(pin2, LOW);
  Serial.println("led>>off");
  delay(500);

  digitalWrite(pin2, HIGH);
  delay(2000);
  digitalWrite(pin2, LOW);
  delay(1000);

  digitalWrite(pin2, HIGH);
  delay(2500);
  digitalWrite(pin2, LOW);
  delay(500);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}