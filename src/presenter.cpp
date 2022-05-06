// Copyright (c) 2022 Inaba (@hollyhockberry)
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php

#include "presenter.h"
#include <M5Unified.h>

namespace {

uint32_t color(Presenter::State state) {
  switch (state) {
  case Presenter::State::Standby:
    return 0;
  case Presenter::State::NotConnected:
    return 0xff0000;
  case Presenter::State::Connected:
    return 0x00ff00;
  default:
    return 0;
  }
}

}  // namespace

void Presenter::begin() {
  switch (M5.getBoard()) {
  case lgfx::boards::board_M5ATOM:
  case lgfx::boards::board_M5AtomPsram:
  case lgfx::boards::board_M5AtomU:
  case lgfx::boards::board_M5StampPico:
    led_.setPin(G27);
    led_.setBrightness(24);
    led_.begin();
    break;
  default:
    // TODO: not implement
    break;
  }
}

void Presenter::update(State state) {
  if (state_ == state) return;
  state_ = state;

  switch (M5.getBoard()) {
  case lgfx::boards::board_M5ATOM:
  case lgfx::boards::board_M5AtomPsram:
  case lgfx::boards::board_M5AtomU:
  case lgfx::boards::board_M5StampPico:
    led_.setPixelColor(0, color(state_));
    led_.show();
    break;
  default:
    // TODO: not implement
    break;
  }
}
