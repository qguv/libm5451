#include <Sixteen.h>

#define DATAPIN  2
#define CLOCKPIN 3

Sixteen display = Sixteen(DATAPIN, CLOCKPIN);
void setup() {}
void loop() {
  display.digitTest();
}
