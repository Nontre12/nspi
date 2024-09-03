#include "nspi_console.h"

// libnx
#ifdef __SWITCH__
#include <switch.h>
#include <unistd.h>
#else
#include "nspi_linux_switch.h"
#endif
#include <iostream>

#include "nspi_logger.h"

nspi::Console::Console() { this->init(); }

nspi::Console::~Console() { this->clean(); }

void nspi::Console::update() const {
  consoleUpdate(nullptr);
  consoleClear();
}

static int debug_fd = -1;
void nspi::Console::init() {
  consoleInit(nullptr);

  consoleDebugInit(debugDevice::debugDevice_NULL);

#ifndef NDEBUG
  debug_fd = nxlinkStdioForDebug();
  if (debug_fd < 0) {
    Logger::error("Could not establish connection with nxlink server");
  } else {
    Logger::debug("Successfully established connection with nxlink server");
  }
#endif
}

void nspi::Console::clean() {
  consoleExit(nullptr);

#ifndef NDEBUG
  // close nxlink debug fd
  if (debug_fd > -1) {
    close(debug_fd);
  }
#endif
}
