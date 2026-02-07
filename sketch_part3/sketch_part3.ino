#include "testasm.h"

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);

  for (uint8_t n = 0; n <= 13; ++n) {
    unsigned int res = testasm(n, 0);
    Serial.print("fib(");
    Serial.print(n);
    Serial.print(") = ");
    Serial.println(res);
  }
  // incorrect res (true results need to be represented with more than 8'b)
  Serial.print("fib(15) != ");
  Serial.println(testasm(15, 0));
  Serial.print("fib(20) != ");
  Serial.println(testasm(20, 0));

  pinMode (13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (13, HIGH);
  delay(400);
  digitalWrite (13, LOW);
  delay(400);
}
