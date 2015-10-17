#include <Sixteen.h>

#define DATAPIN  2
#define CLOCKPIN 3

Sixteen display = Sixteen(DATAPIN, CLOCKPIN);
void setup() {}
void loop() {
  char s[21];
  s[0] = '\0';
  strcat(&s[0], "0123456789");
  strcat(&s[0], &display.doubleDigits[0]);
  display.scroll(&s[0], 250);
}
