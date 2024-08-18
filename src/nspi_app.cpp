#include "nspi_app.h"

nspi::App::App() : quit(false) {}

nspi::App::~App() {}

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
  u64 kDown = this->pad.getButtonsDown();
  if (kDown & HidNpadButton_Plus) {
    this->quit = true;
  }

  // delegate input to current menu after critical input checks
  this->menu.handleInput();
}

void nspi::App::draw() {
  this->menu.draw();
  this->console.update();
}

void nspi::App::run() { this->mainLoop(); }