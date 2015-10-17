#include "Arduino.h"
#include "Sixteen.h"
#include <avr/pgmspace.h>

// constructor
Sixteen::Sixteen(int dataPinIn, int clockPinIn) {

  // instance variables
  dataPin  = dataPinIn;
  clockPin = clockPinIn;

  // open the required pins
  pinMode(dataPin,  OUTPUT);
  pinMode(clockPin, OUTPUT);

  // ensure we're starting low
  digitalWrite(dataPin,  LOW);
  digitalWrite(clockPin, LOW);
}

// Sixteen::writeBit sends a single bit to the data stream, also
// pulsing the clock.
void Sixteen::writeBit(bool bit) {

  // set the bit
  digitalWrite(dataPin, bit);

  // pulse the clock
  digitalWrite(clockPin, HIGH);
  delay(1);
  digitalWrite(clockPin, LOW);
}

// Sixteen::writeMask sets all 32 LEDs at once using a bitmask.
void Sixteen::writeMask(uint32_t frame) {

  // write the 'enable' bit and the first disconnected pin
  writeBit(true); writeBit(false);

  // write the bitmask, bit by bit
  for (int i = 0; i < 32; i++) {
    writeBit((bool) ((frame >> i) & 1));
  }

  // write to the other two disconnected pins
  writeBit(false); writeBit(false);
}

// make a 16-bit digit out of a character. Note that this is not
// right-side or left-side specific and would not be displayable on
// its own. Use 'print' for that.
uint16_t Sixteen::charMask(char c) {

  // lower-case letters are treated as capitals
  if (c > 'a' && c < 'z') { c -= 'z' - 'Z'; }

  // if you ask out of scope, the response is a blank digit
  if ((c < 0) || (c > lastChar)) { return 0u; }

  // otherwise, consult the font map
  return font[c];
}

void Sixteen::writeChars(char lchar, char rchar) {

  // left digit starts at bit 8 and continues t/m bit 23, so we'll push our
  // idealized character 8 bits forward to fill the left digit
  uint32_t lframe = (uint32_t) charMask(lchar);
  lframe <<= 8;

  // right digit takes up 0 t/m 7 and 24 t/m 31 (weird, right?) so we'll split
  // the bit in two, printing the bottom as normal and cutting off and pushing
  // forward the top half of the bottom one
  uint32_t rframe_high, rframe_low;
  rframe_low = (uint32_t) charMask(rchar);

  rframe_high = rframe_low & 0xff00u;
  rframe_low &= 0x00ffu;

  // push the high segment to its place
  rframe_high <<= 16;

  // write the segments
  writeMask(rframe_low | lframe | rframe_high);
}

void Sixteen::scroll(char *message, int delayMilliseconds) {

  // the left cell starts empty
  char left = 0;
  char *right = message;

  // iterate through the string; left is one char behind
  do {
    writeChars(left, *right);
    left = *right;
    right++;
    delay(delayMilliseconds);
  } while (left != '\0');

  // one empty frame
  writeChars(0, 0);
  delay(delayMilliseconds);
}

// display each digit for inspection
void Sixteen::digitTest(char startAt) {
  for (char i = startAt; i <= lastChar; i += 2) {
    writeChars(i, i + 1);
    delay(1500);
  }
}
