#include "nspi_pad.h"

// libnx
#include <switch.h>

nspi::Pad::Pad() { this->init(); }

nspi::Pad::~Pad() {}

void nspi::Pad::update() { padUpdate(&this->pad); }

u64 nspi::Pad::getButtonsDown() const { return padGetButtonsDown(&this->pad); }

void nspi::Pad::init() {
  padConfigureInput(1, HidNpadStyleSet_NpadStandard);
  padInitializeDefault(&this->pad);
}
