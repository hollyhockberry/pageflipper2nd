// Copyright (c) 2022 Inaba (@hollyhockberry)
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php

#include <Adafruit_NeoPixel.h>

class Presenter {
 public:
  enum State {
    Standby,
    NotConnected,
    Connected,
  };
  Presenter() : state_(State::Standby), led_(1) {}

  void begin();
  void update(State state);
 private:
  State state_;
  Adafruit_NeoPixel led_;

  Presenter(const Presenter&);
  void operator=(const Presenter&);
};
