#include <Sixteen.h>

#define DATAPIN  2
#define CLOCKPIN 3

Sixteen display = Sixteen(DATAPIN, CLOCKPIN);

void setup() {

  // enable arduino data and clock pin output
  pinMode(DATAPIN,  OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);

  // ensure that we're starting low
  digitalWrite(DATAPIN,  LOW);
  digitalWrite(CLOCKPIN, LOW);
}

void loop() {
  display.print();
  delay(500);
}
