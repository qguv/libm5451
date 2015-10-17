// ensure this library description is only included once
#ifndef Sixteen_h
#define Sixteen_h
#include "Arduino.h"

class Sixteen {

  public:
    Sixteen(int, int);
    int      dataPin;
    int      clockPin;

    uint16_t charMask(char);
    void     writeBit(bool);
    void     writeMask(uint32_t);
    void     writeChars(char, char);
    void     scroll(char *, int);
    void     digitTest();

    // maps characters to 16-segment bitmaps
    const static int firstChar = 48;
    const static int lastChar  = 65;

    const uint16_t font[1 + lastChar - firstChar] = {
      0xf5f5, // 0 (48)
      0x6001, // 1 (49)
      0xd4d4, // 2 (50)
      0xd495, // 3 (51)
      0xc181, // 4 (52)
      0x9595, // 5 (53)
      0x95d5, // 6 (54)
      0x5401, // 7 (55)
      0xd5d5, // 8 (56)
      0xd595, // 9 (57)
      0x594d, // 10 (58 custom)
      0x4141, // 11 (59 custom)
      0xd14c, // 12 (60 custom)
      0xd145, // 13 (61 custom)
      0xc941, // 14 (62 custom)
      0x9945, // 15 (63 custom)
      0xd5c1, // A (64)
      0xdc9d, // B (65)
    };

    // some custom double-digits
    const static char ten       = 58;
    const static char eleven    = 59;
    const static char twelve    = 60;
    const static char thirteen  = 61;
    const static char fourteen  = 62;
    const static char fifteen   = 63;
    const static char sixteen   = 91;
    const static char seventeen = 92;
    const static char eighteen  = 93;
    const static char nineteen  = 94;
    const char doubleDigits[7] = {ten, eleven, twelve, thirteen, fourteen,
      fifteen, '\0'};
};

#endif
