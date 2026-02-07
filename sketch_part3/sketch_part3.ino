#include "testasm.h"

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  // Serial.print("The sum of 3 and 4 is: ");
  // Serial.println(testasm(3, 4));
  for (uint8_t n = 0; n <= 13; ++n) {
    unsigned int res = testasm(n, 0);
    Serial.print("fib(");
    Serial.print(n);
    Serial.print(") = ");
    Serial.println(res);
  }
  pinMode (13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (13, HIGH);
  delay(400);
  digitalWrite (13, LOW);
  delay(400);
}
