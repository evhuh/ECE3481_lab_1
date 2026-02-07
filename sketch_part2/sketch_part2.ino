#include "testasm.h"

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);

  Serial.print("testasm(3, 4) = ");
  Serial.println(testasm(3, 4));

  Serial.print("testasm(4, 3) = ");
  Serial.println(testasm(4, 3));

  Serial.print("testasm(10, 3) = ");
  Serial.println(testasm(10, 3));

  Serial.print("testasm(3, 10) = ");
  Serial.println(testasm(3, 10));

  Serial.print("testasm(0, 0) = ");
  Serial.println(testasm(0, 0));

  Serial.print("testasm(0, 255) = ");
  Serial.println(testasm(0, 255));

  Serial.print("testasm(67, 76) = ");
  Serial.println(testasm(67, 76));

  Serial.print("testasm(255, 1) = ");
  Serial.println(testasm(255, 1));

  Serial.print("testasm(128, 128) = ");
  Serial.println(testasm(128, 128));

  Serial.print("testasm(255, 255) = ");
  Serial.println(testasm(255, 255));
  
  pinMode (13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (13, HIGH);
  delay(400);
  digitalWrite (13, LOW);
  delay(400);
}
