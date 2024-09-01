#include "nspi_pad.h"

// libnx
#ifdef __SWITCH__
#include <switch.h>
#else
#include "nspi_linux_switch.h"
#endif

nspi::Pad::Pad() { this->init(); }

void nspi::Pad::update() { padUpdate(&this->pad); }

uint64_t nspi::Pad::getButtonsDown() const { return padGetButtonsDown(&this->pad); }

HidAnalogStickState nspi::Pad::getStickPos(const uint8_t &id) const {
  return padGetStickPos(&this->pad, id);
}

void nspi::Pad::init() {
  padConfigureInput(1, HidNpadStyleSet_NpadStandard);
  padInitializeDefault(&this->pad);
}
