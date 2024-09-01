#include "nspi_app.h"

// libnx
#ifdef __SWITCH__
#include <switch.h>
#else
#include "nspi_linux_switch.h"
#endif

#include "nspi_title_selector_menu.h"

nspi::App::App() : quit(false) { this->init(); }

nspi::App::~App() { this->clean(); }

void nspi::App::init() { socketInitializeDefault(); }

void nspi::App::clean() { socketExit(); }

bool nspi::App::shouldClose() const { return this->quit || !appletMainLoop(); }

void nspi::App::mainLoop() {
  while (!this->shouldClose()) {
    this->handleInput();
    // some logic ???
    this->draw();
  }
}

void nspi::App::handleInput() {
  this->pad.update();
  uint64_t kDown = this->pad.getButtonsDown();
  if (kDown & HidNpadButton_Plus) {
    this->quit = true;
  }

  // delegate input to current menu after critical input checks
  this->menuManager.handleInput();
}

void nspi::App::draw() const {
  this->menuManager.draw();
  this->console.update();
}

void nspi::App::run() { this->mainLoop(); }
