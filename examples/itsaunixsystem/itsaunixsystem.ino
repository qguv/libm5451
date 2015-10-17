#include <Sixteen.h>

#define DATAPIN  2
#define CLOCKPIN 3
#define RANDPIN  0 // n.b. this is an analog pin
#define rchar random(display.firstChar, display.lastChar + 1)

Sixteen display = Sixteen(DATAPIN, CLOCKPIN);
void setup() {
  // just for show; doesn't need to be secure
  randomSeed(analogRead(0));
}
void loop() {
  do {
    display.writeChars(rchar, rchar);
    delay(10);
  } while (true);
}
