#include <Sixteen.h>

#define DATAPIN  2
#define CLOCKPIN 3
#define RANDPIN  0 // n.b. this is an analog pin

Sixteen display = Sixteen();

void setup() {

  display.addScreen(DATAPIN, CLOCKPIN);

  // use analog noise to generate random numbers
  randomSeed(analogRead(0));

  // fill the screen
  display.writeMask(0, ~(uint32_t) 0);
  delay(500);
}

// get a random character glyph, but not a blank one
char rchar() {
  char c;
  do {
    c = random(display.lastChar + 1);
  } while (!display.charMask(c));
  return c;
}

// repeatedly display arbitrary characters
void loop() {
  display.writeChars(0, rchar(), rchar());
  delay(70);
}
