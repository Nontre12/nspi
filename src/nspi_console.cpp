#include "nspi_console.h"

// libnx
#ifdef __SWITCH__
#include <switch.h>
#else
#include "nspi_linux_switch.h"
#endif

nspi::Console::Console() { this->init(); }

nspi::Console::~Console() { this->clean(); }

void nspi::Console::update() const {
  consoleUpdate(nullptr);
  consoleClear();
}

void nspi::Console::init() { consoleInit(nullptr); }

void nspi::Console::clean() { consoleExit(nullptr); }
