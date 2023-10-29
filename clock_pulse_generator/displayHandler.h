#ifndef DISPLAY_HANDLER_H
#define DISPLAY_HANDLER_H

#include "globals.h"

/* * * *  2281BS  * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *         f 1 b a 2
 *       --+-+-+-+-+--
 *       |    8.8.   |
 *       --+-+-+-+-+--
 *         e d c g .
 *
 */

namespace display {

namespace {

constexpr uint8_t _TERMINAL = ANODE;
constexpr uint8_t _CHAR_PLACES = 2;
constexpr uint8_t _ANIMATION_DELAY = 64;

const uint8_t _chars[_CHAR_PLACES] = {
  mcu::CHAR_0,
  mcu::CHAR_1
};
const uint8_t _segments[8] = {
  mcu::SEG_g,
  mcu::SEG_f,
  mcu::SEG_e,
  mcu::SEG_d,
  mcu::SEG_c,
  mcu::SEG_b,
  mcu::SEG_a,
  mcu::SEG_dp
};

}  // namespace

uint16_t buffer = 0x0000;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setChars(uint8_t char1, uint8_t char0) {
  buffer = char1 << 8 | char0;
}

void clear() {
  setChars(symbol::EMPTY, symbol::EMPTY);
}

void manualModeAnimation(uint32_t delay) {
  const uint8_t frame[2][4]{
    { symbol::DUSK, symbol::SET, symbol::UNDERSCORE },
    { symbol::DAWN, symbol::RISE, symbol::OVERSCORE }
  };
  switch (delay / _ANIMATION_DELAY) {
    case 0:
      setChars(buffer >> 8, frame[buttonPressed][0]);
      break;
    case 1:
      setChars(buffer >> 8, frame[buttonPressed][1]);
      break;
    case 2:
      setChars(frame[buttonPressed][0], frame[buttonPressed][2]);
      break;
    case 3:
      setChars(frame[buttonPressed][1], frame[buttonPressed][2]);
      break;
    default:
      setChars(frame[buttonPressed][2], frame[buttonPressed][2]);
      break;
  }
}

void manualModeDisplay() {
  if (buttonPressed) {
    setChars(symbol::OVERSCORE, symbol::OVERSCORE);
  } else {
    setChars(symbol::UNDERSCORE, symbol::UNDERSCORE);
  }
}

void handler() {
  static uint8_t actualChar = 0;

  for (uint8_t i = 0; i < _CHAR_PLACES; i++) {  // turn display off
    digitalWrite(_chars[i], !_TERMINAL);
  }
  uint8_t buf = buffer >> 8 * actualChar;
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(_segments[i], ((buf >> i) + _TERMINAL) & 1);
  }

  digitalWrite(_chars[actualChar], _TERMINAL);

  actualChar += 1;
  actualChar %= _CHAR_PLACES;  // scan through charplaces
}

}  // display namespace

#endif