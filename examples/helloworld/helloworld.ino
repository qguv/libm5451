#include <Sixteen.h>

#define DATAPIN  2
#define CLOCKPIN 3

Sixteen display = Sixteen(DATAPIN, CLOCKPIN);
void setup() {}
void loop() { display.scroll("Hello world. In Zweden vocht groepje quakers b! sexfilm.   Pack my box with five dozen liquor jugs.   Portez ce vieux bon whiskys au juge blond qui fume.", 300); }
