#include "nspi_pad.h"

// libnx
#include <switch.h>

nspi::Pad::Pad() { this->init(); }

void nspi::Pad::update() { padUpdate(&this->pad); }

u64 nspi::Pad::getButtonsDown() const { return padGetButtonsDown(&this->pad); }

HidAnalogStickState nspi::Pad::getStickPos() const {
  return padGetStickPos(&this->pad, 0);
}

void nspi::Pad::init() {
  padConfigureInput(1, HidNpadStyleSet_NpadStandard);
  padInitializeDefault(&this->pad);
}
