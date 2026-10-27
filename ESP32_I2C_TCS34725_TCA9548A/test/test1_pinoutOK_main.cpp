//test pin2 out led on off, result is ok!

#include <Arduino.h>
//#include <iic_test_color.cpp>
#define pin2 2   //gpio pin 2 for led
#define pin3 3 

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  pinMode(pin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("hello,esp32");
  digitalWrite(pin2, HIGH);
  Serial.println("led>>on");
  delay(5000);

  digitalWrite(pin2, LOW);
  Serial.println("led>>off");
  delay(2000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}