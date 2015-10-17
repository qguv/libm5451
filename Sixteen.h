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
    void     digitTest(char);

    /* ===== GLYPH STORAGE =====
     *
     *   _A_ _C_                   segments
     *  |\  |  /|             ________|________
     *  8 9 B D E            /                 \
     *  |  \|/  |            FEDC BA98 7654 3210
     *   -7- -F-    0x0000 = 0000 0000 0000 0000
     *  |  /|\  |            \_________________/
     *  6 5 3 1 0                     |
     *  |/  |  \|                binary bits
     *   -4- -2-
     *
     * Segments that are lit have a bit; those that aren't, don't.
     *
     * For example, here is the letter 'E':
     *
     *   _A_ _C_
     *  |
     *  8
     *  |                    FEDC BA98 7654 3210
     *   -7-        0x15d4 = 0001 0101 1101 0100
     *  |
     *  6
     *  |
     *   -4- -2-
     *
     * Here is the letter 'X':
     *
     *
     *   \     /
     *    9   D
     *     \ /               FEDC BA98 7654 3210
     *              0x2222 = 0010 0010 0010 0010
     *     / \
     *    5   1
     *   /     \
     *
     * Not so hard, right? It gets easier; you'll start to notice patterns like
     * the '2' digits in the hex of the above letter 'X'.
     *
     *
     * ===== DATA TRANSMISSIYN =====
     *
     * The glyph storage bits correspond, in order, to the bits transmitted to the
     * 16-segment chip.
     *
     * To send a bit to the chip, we set the voltage of the DATA pin to HIGH
     * (5V) or LOW (GND) w/r/t ground. Then the voltage on the clock pin is set
     * to HIGH and back to LOW again to indicate that the chip should now read
     * what we've set.
     *
     * Sending bits alone doesn't mean anything. These bits have to be part of
     * a message. Each message is composed of 36 bits.
     *
     * message = 10WW WWWW WWXX
     *           XXXX XXYY YYYY
     *           YYZZ ZZZZ ZZ00 (36 bits total)
     *
     * The first bit in the mesage must be a HIGH bit to indicate that we have
     * begun a message.
     *
     * The next bit corresponds to a pin that's not connected, so send LOW (it
     * doesn't matter).
     *
     * The body of the message is the payload, namely the settings for each
     * segment in the display. The segments are really strangely laid out:
     *
     *            ___ ___      ___ ___
     *           |\  |  /|    |\  |  /|
     *  HUNK Y   | \ | / |    | \ | / |   HUNK Z
     * (third)   |  \|/  |    |  \|/  |  (fourth/last)
     *               '---'        '---'
     *            ___          ___ 
     *           |  /|\  |    |  /|\  |
     *  HUNK X   | / | \ |    | / | \ |   HUNK W
     * (second)  |/  |  \|    |/  |  \|  (transmitted first)
     *           '---'---'    '---'---'
     *
     * The bottom hunk (W) of the right digit is sent first. Then comes the
     * bottom hunk (X) of the left digit, then the top hunk (Y) of the left
     * digit, then the top hunk (Z) of the right.
     *
     * The last two bits correspond to pins that aren't connected, so send LOW
     * (it doesn't matter).
     */

    // maps ascii characters to 16-segment bitmaps
    const static int lastChar = 96;
    const uint16_t font[1 + lastChar] = {

      // reserved for null-terminator
      0x0000, // ASCII 0

      // customizable
      0x0000, // custom 1
      0x0000, // custom 2
      0x0000, // custom 3
      0x0000, // custom 4
      0x0000, // custom 5
      0x0000, // custom 6
      0x0000, // custom 7
      0x0000, // custom 8
      0x0000, // custom 9

      // two-digit numbers in the non-printable ascii area
      0x594d, // "10"
      0x4141, // "11"
      0xd14c, // "12"
      0xd145, // "13"
      0xc941, // "14"
      0x9945, // "15"
      0x994d, // "16"
      0x5141, // "17"
      0xd94d, // "18"
      0xd945, // "19"
      0x988c, // "€" (20)
      0x4cd1, // "21"

      // another customizable block
      0x0000, // custom 22
      0x0000, // custom 23
      0x0000, // custom 24
      0x0000, // custom 25
      0x0000, // custom 26
      0x0000, // custom 27
      0x0000, // custom 28
      0x0000, // custom 29
      0x0000, // custom 30

      // customized digit
      0x4c99, // "31"

      // printable ASCII
      0x0000, //   (32 whitespace)
      0x4145, // ! (33 custom ij diagraph)
      0x0900, // " (34)
      0xc9c9, // # (35)
      0x9d9d, // $ (36)
      0xadad, // % (37)
      0x383d, // & (38)
      0x0800, // ' (39)
      0x180c, // ( (40)
      0x0c18, // ) (41)
      0xaaaa, // * (42)
      0x8888, // + (43)
      0x0018, // , (44)
      0x8080, // - (45)
      0x0010, // . (46)
      0x2020, // / (47)
      0x7575, // 0 (48)
      0x6001, // 1 (49)
      0xd4d4, // 2 (50)
      0xd495, // 3 (51)
      0xc181, // 4 (52)
      0x9595, // 5 (53)
      0x95d5, // 6 (54)
      0x5401, // 7 (55)
      0xd5d5, // 8 (56)
      0xd595, // 9 (57)
      0x0410, // : (58)
      0x0418, // ; (59)
      0x2002, // < (60)
      0x8094, // = (61)
      0x0220, // > (62)
      0xd404, // ? (63)
      0xd54d, // @ (64)
      0xd5c1, // A (65)
      0xdc1d, // B (66)
      0x1554, // C (67)
      0x5c1d, // D (68)
      0x15d4, // E (69)
      0x15c0, // F (70)
      0x9555, // G (71)
      0xc1c1, // H (72)
      0x1c1c, // I (73)
      0x1c58, // J (74)
      0x21c2, // K (75)
      0x0154, // L (76)
      0x6341, // M (77)
      0x4343, // N (78)
      0x5555, // O (79)
      0xd5c0, // P (80)
      0x5557, // Q (81)
      0xd542, // R (82)
      0x9595, // S (83)
      0x1c08, // T (84)
      0x4155, // U (85)
      0x2160, // V (86)
      0x4163, // W (87)
      0x2222, // X (88)
      0x2208, // Y (89)
      0x3434, // Z (90)
      0x180c, // [ (91)
      0x0202, // \ (92)
      0x0c18, // ] (93)
      0x0022, // ^ (94)
      0x0014, // _ (95)
      0x0200, // ` (96)
    };

    // some custom digits, replacing difficult-to-read ascii
    const static char euro      = 38;
    const static char ten       = 10;
    const static char eleven    = 11;
    const static char twelve    = 12;
    const static char thirteen  = 13;
    const static char fourteen  = 14;
    const static char fifteen   = 15;
    const static char sixteen   = 16;
    const static char seventeen = 17;
    const static char eighteen  = 18;
    const static char nineteen  = 19;
    const static char twentyone = 21;
};

#endif
