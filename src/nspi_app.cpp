#include "nspi_app.h"

nspi::App::App() : quit(false) {}

nspi::App::~App() {}

void nspi::App::mainLoop() {
  while (!this->shouldClose()) {
    this->pad.update();
    u64 kDown = this->pad.getButtonsDown();

    if (kDown & HidNpadButton_Plus) {
      this->quit = true;
    }

    this->menu.handleInput();
    this->menu.print();

    this->console.update();
  }
}

bool nspi::App::shouldClose() const { return this->quit || !appletMainLoop(); }

void nspi::App::run() { this->mainLoop(); }