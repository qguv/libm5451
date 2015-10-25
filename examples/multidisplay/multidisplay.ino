#include <Sixteen.h>

Sixteen display = Sixteen();

void setup() {
  display.addScreen(11, 10);
  display.addScreen(9, 8);
  display.addScreen(7, 6);
  display.addScreen(5, 4);
  display.addScreen(3, 2);
}

void loop() {
  display.scroll("Hello world.", 100);
  display.scroll("(also Sebastius)", 75);
  display.scroll("In Zweden vocht groepje quakers b! sexfilm.   Pack my box with five dozen liquor jugs.   Portez ce vieux bon whiskys au juge blond qui fume.", 100);
}
