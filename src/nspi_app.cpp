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

    // code goes here
    if (kDown & HidNpadButton_A) {
      this->menu.__debug_push_back_list_element(
          {"1000000000000000", "EUR", "Tiles of Zestyria", 12});
    }

    if (kDown & HidNpadButton_Up) {
      // focus up
    }

    if (kDown & HidNpadButton_Down) {
      // focus down
    }

    this->menu.print();

    this->console.update();
  }
}

bool nspi::App::shouldClose() const { return this->quit || !appletMainLoop(); }

void nspi::App::run() { this->mainLoop(); }