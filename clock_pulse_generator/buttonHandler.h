#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include "globals.h"
#include "displayHandler.h"

namespace button {

namespace {

constexpr uint32_t _DOUBLE_TAP_DELAY = 256;
constexpr uint32_t _LONG_TAP_DELAY = 1024;

// Button states patterns
constexpr uint8_t _PRESSED = 0b10000000;
constexpr uint8_t _RELEASED = 0b01111111;

uint32_t _buttonEventTime = 0;

}

uint8_t bounceSequence() {
  static uint8_t sequence;
  sequence = (sequence << 1) | digitalRead(mcu::BUTTON);
  return sequence;
}

void manual_mode_handler() {
  uint32_t handleTime = millis();
  if (buttonPressed) {
    digitalWrite(mcu::OUTPUT_SIGNAL, HIGH);
  } else {
    digitalWrite(mcu::OUTPUT_SIGNAL, LOW);
  }
  if(ANIMATION_MODE) {
    display::manualModeAnimation(handleTime - _buttonEventTime);
  } else {
    display::manualModeDisplay();
  }
}

void auto_mode_handler(bool longPress) {
  static uint16_t count = 0;
  static uint8_t speedModeLag = 0;
  static uint8_t bandIndex = mcu::INIT_INDEX;
  uint16_t value = mcu::MILLIS_VALUES[bandIndex][1];
  if (longPress) {
    if (speedModeLag > 3) {
      if (millis() / (_DOUBLE_TAP_DELAY / 2) & 1) {
        if (count == 0) bandIndex = (bandIndex + 1) % mcu::BANDS;
        count++;
      } else {
        count = 0;
      }
      display::buffer = value;
    } else {
      if (millis() / _DOUBLE_TAP_DELAY & 1) {
        display::clear();
      } else {
        display::buffer = value;
      }
      if (millis() / (_DOUBLE_TAP_DELAY * 2) & 1) {
        if (count == 0) {
          bandIndex = (bandIndex + 1) % mcu::BANDS;
          speedModeLag++;
        }
        count++;
      } else {
        count = 0;
      }
    }
  } else {
    count = 0;
    speedModeLag = 0;
    display::buffer = value;
  }
  digitalWrite(
    mcu::OUTPUT_SIGNAL,
    millis() / mcu::MILLIS_VALUES[bandIndex][0] & 1);
}

void handler() {
  static uint8_t quickTapsCount = 0;
  static bool longPress = false;
  uint8_t sequence = bounceSequence();
  if (sequence == _PRESSED) {
    _buttonEventTime = millis();
    buttonPressed = true;
    quickTapsCount++;
    if (quickTapsCount == 2) {
      mcu::manualMode = !mcu::manualMode;
      quickTapsCount = 0;
    }
  }
  if (sequence == _RELEASED) {
    _buttonEventTime = millis();
    buttonPressed = false;
    longPress = false;
  }
  if (millis() - _buttonEventTime > _DOUBLE_TAP_DELAY) {
    quickTapsCount = 0;
  }
  if (buttonPressed && (millis() - _buttonEventTime > _LONG_TAP_DELAY)) {
    longPress = true;
  }
  if (mcu::manualMode) manual_mode_handler();
  else auto_mode_handler(longPress);
}

}  // button namespace

#endif