#ifndef MCU_HANDLER_H
#define MCU_HANDLER_H

#include "globals.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  ATtiny24  ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                                  _______
 *                            VCC <|• \_/--|> GND
 *                  XTAL1     10  <| OS  f_|>  0  A0   AREF
 *                  XTAL2      9  <|_e   1 |>  1  A1   AIN0  TXD
 *                  Reset     11  <|_dp  b_|>  2  A2   AIN1  RXD
 *            INT0  OC0A       8  <|_d   a_|>  3  A3
 *                  OC0B   A7  7  <|_c   0 |>  4  A4   SCK   SCK  SCL
 * OC1A  SDA  DI    MOSI   A6  6  <|_g  TB_|>  5  A5   MISO  DO   OC1B
 *                                  -------
 */

namespace mcu {

constexpr uint8_t BUTTON = 5;
constexpr uint8_t OUTPUT_SIGNAL = 10;

constexpr uint8_t SEG_a = 3;
constexpr uint8_t SEG_b = 2;
constexpr uint8_t SEG_c = 7;
constexpr uint8_t SEG_d = 8;
constexpr uint8_t SEG_e = 9;
constexpr uint8_t SEG_f = 0;
constexpr uint8_t SEG_g = 6;
constexpr uint8_t SEG_dp = 11;

constexpr uint8_t CHAR_0 = 4;
constexpr uint8_t CHAR_1 = 1;

bool manualMode = true;

// half period of 250 ms for a 2 Hz wave
constexpr uint8_t INIT_INDEX = 4;

// Shorted range of half periods in millis
// with Hz values to show on two digit display
const uint8_t BANDS = 10;
const uint16_t MILLIS_VALUES[BANDS][2] = {
  { 4835, symbol::COMMA << 8 | symbol::ONE  },    // 0.1 Hz
  { 2413, symbol::COMMA << 8 | symbol::TWO  },    // 0.2 Hz
  { 967,  symbol::COMMA << 8 | symbol::FIVE },    // 0.5 Hz
  { 483,  symbol::EMPTY << 8 | symbol::ONE  },    //   1 Hz
  { 241,  symbol::EMPTY << 8 | symbol::TWO  },    //   2 Hz
  { 97,   symbol::EMPTY << 8 | symbol::FIVE },    //   5 Hz
  { 48,   symbol::ONE   << 8 | symbol::ZERO },    //  10 Hz
  { 24,   symbol::TWO   << 8 | symbol::ZERO },    //  20 Hz
  { 10,   symbol::FIVE  << 8 | symbol::ZERO },    //  50 Hz
  { 5,    symbol::NINE  << 8 | symbol::SEVEN}     //  97 Hz
};

}  // mcu namespace

#endif