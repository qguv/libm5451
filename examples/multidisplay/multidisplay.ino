#include <Sixteen.h>

#define DATAPINLEFT   2
#define CLOCKPINLEFT  3
#define DATAPINRIGHT  4
#define CLOCKPINRIGHT 5

Sixteen display = Sixteen();

void setup() {
  display.addScreen(DATAPINLEFT, CLOCKPINLEFT);
  display.addScreen(DATAPINRIGHT, CLOCKPINRIGHT);
}

void loop() {
  display.scroll("Hello world.", 150);
  display.scroll("In Zweden vocht groepje quakers b! sexfilm.   Pack my box with five dozen liquor jugs.   Portez ce vieux bon whiskys au juge blond qui fume.", 150);
}
