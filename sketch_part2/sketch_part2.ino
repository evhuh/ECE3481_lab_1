#include "testasm.h"

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);

  Serial.print("3 and 4: ");
  Serial.println(testasm(3, 4));
  Serial.print("255 and 255: ");
  Serial.println(testasm(255, 255));
  Serial.print("0 and 0: ");
  Serial.println(testasm(0, 0));
  Serial.print("67 and 76: ");
  Serial.println(testasm(67, 76));
  
  pinMode (13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (13, HIGH);
  delay(400);
  digitalWrite (13, LOW);
  delay(400);
}
