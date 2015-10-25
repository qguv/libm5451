#include <Sixteen.h>

#define DATAPIN  3
#define CLOCKPIN 2

Sixteen display = Sixteen();
void setup() { display.addScreen(DATAPIN, CLOCKPIN); }
void loop() { display.digitTest(0, display.ten); }
