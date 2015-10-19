#include <Sixteen.h>

#define DATAPINLEFT   A3
#define CLOCKPINLEFT  A2
#define DATAPINMID    A1
#define CLOCKPINMID   A0
#define DATAPINRIGHT  11
#define CLOCKPINRIGHT 10

Sixteen display = Sixteen();

void setup() {
  display.addScreen(DATAPINLEFT, CLOCKPINLEFT);
  display.addScreen(DATAPINMID, CLOCKPINMID);
  display.addScreen(DATAPINRIGHT, CLOCKPINRIGHT);
}

void loop() {
  display.scroll("Hello world.", 100);
  display.scroll("(also Sebastius)", 75);
  display.scroll("In Zweden vocht groepje quakers b! sexfilm.   Pack my box with five dozen liquor jugs.   Portez ce vieux bon whiskys au juge blond qui fume.", 100);
}
