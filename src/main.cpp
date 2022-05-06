// Copyright (c) 2022 Inaba (@hollyhockberry)
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php

#include <M5Unified.h>
#include <BleMouse.h>
#include "presenter.h"

namespace {

constexpr uint32_t SLEEPTIME_MS = 120 * 1000;

BleMouse mouse("M5Flipper2");
Presenter presenter;

void move(uint8_t dx, uint8_t dy) {
  mouse.move(dx, dy);
  delay(1);
}

void move(bool forward) {
  const uint8_t dx = 100 * (forward ? -1 : 1);
  for (auto i = 0; i < 10; ++i) {
    move(dx, 0);
  }
  mouse.click(MOUSE_LEFT);
}

void sleep() {
  presenter.update(Presenter::State::Standby);
  mouse.end();

  switch (M5.getBoard()) {
  case lgfx::boards::board_M5ATOM:
  case lgfx::boards::board_M5AtomPsram:
  case lgfx::boards::board_M5AtomU:
  case lgfx::boards::board_M5StampPico:
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_39, LOW);
    esp_deep_sleep_start();
    break;
  default:
    // TODO: not implement
    break;
  }
  for (;;) {}
}

}  // namespace

void setup() {
  M5.begin();
  mouse.begin();
  M5.BtnA.setHoldThresh(250);
  presenter.begin();
  presenter.update(Presenter::State::NotConnected);
}

void loop() {
  if (!mouse.isConnected()) return;
  presenter.update(Presenter::State::Connected);
  M5.update();
  if (M5.BtnA.releasedFor(SLEEPTIME_MS)) {
    sleep();
  } else if (M5.BtnA.wasClicked()) {
    move(true);
  } else if (M5.BtnA.wasHold()) {
    move(false);
  }
}
