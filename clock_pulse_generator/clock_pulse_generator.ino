/* ATtiny24 code
 *
 * Breadboard Clock Pulse Generator with manual and automatic operating modes.
 * In manual mode the circuit operates as a debounced button. In automatic mode
 * it operates as a square wave generator. You could bear through a preset list
 * of frequencies in a range from 0.1 Hz to 97 Hz.
 */

#include "globals.h"
#include "mcuHandler.h"
#include "displayHandler.h"
#include "buttonHandler.h"

void setup() {

  pinMode(mcu::BUTTON, INPUT_PULLUP);
  pinMode(mcu::OUTPUT_SIGNAL, OUTPUT);
  pinMode(mcu::SEG_a, OUTPUT);
  pinMode(mcu::SEG_b, OUTPUT);
  pinMode(mcu::SEG_c, OUTPUT);
  pinMode(mcu::SEG_d, OUTPUT);
  pinMode(mcu::SEG_e, OUTPUT);
  pinMode(mcu::SEG_f, OUTPUT);
  pinMode(mcu::SEG_g, OUTPUT);
  pinMode(mcu::CHAR_0, OUTPUT);
  pinMode(mcu::CHAR_1, OUTPUT);

  delay(1);

  // Manual mode indication
  display::setChars(symbol::OVERSCORE, symbol::OVERSCORE);

}

void loop() {

  button::handler();
  display::handler();

}
