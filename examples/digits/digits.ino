#include <Sixteen.h>

#define DATAPIN  2
#define CLOCKPIN 3

Sixteen display = Sixteen();
void setup() { display.addScreen(DATAPIN, CLOCKPIN); }
void loop() { display.digitTest(0, display.ten); }
