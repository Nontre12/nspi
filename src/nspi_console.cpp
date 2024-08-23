#include "nspi_console.h"

// libnx
#include <switch.h>

nspi::Console::Console() { this->init(); }

nspi::Console::~Console() { this->clean(); }

void nspi::Console::update() {
  consoleUpdate(nullptr);
  consoleClear();
}

void nspi::Console::init() { consoleInit(nullptr); }

void nspi::Console::clean() { consoleExit(nullptr); }
