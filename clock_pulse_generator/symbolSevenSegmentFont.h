#ifndef SYMBOL_SEVEN_SEGMENT_FONT_H
#define SYMBOL_SEVEN_SEGMENT_FONT_H

/* ~~~~~  7-Segment Indicator Segments' Coding  ~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *            aaaaa
 *          ff    bb
 *          ff    bb
 *           ggggg
 *         ee    cc
 *         ee    cc
 *          ddddd   dp
 */

namespace symbol {

// Display characters
// segments order:               .abcdefg
constexpr uint8_t EMPTY =      0b00000000;
// Numerals
constexpr uint8_t ZERO =       0b01111110;
constexpr uint8_t ONE =        0b00110000;
constexpr uint8_t TWO =        0b01101101;
constexpr uint8_t FIVE =       0b01011011;
constexpr uint8_t SEVEN =      0b01110010;
constexpr uint8_t NINE =       0b01111011;
// Punctuations
constexpr uint8_t COMMA =      0b00010000;
constexpr uint8_t UNDERSCORE = 0b00001000;
constexpr uint8_t OVERSCORE =  0b01000000;
// Animation characters
constexpr uint8_t DAWN =       0b00111000;
constexpr uint8_t RISE =       0b01000010;
constexpr uint8_t DUSK =       0b01110000;
constexpr uint8_t SET =        0b00001100;

} // symbol namespace

#endif