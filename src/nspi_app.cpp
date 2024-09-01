#include "nspi_app.h"

// libnx
#ifdef __SWITCH__
#include <switch.h>
#else
#include "nspi_linux_switch.h"
#endif

// std
#include <chrono>
#include <thread>

#include "nspi_title_selector_menu.h"

nspi::App::App() : quit(false) { this->init(); }

nspi::App::~App() { this->clean(); }

void nspi::App::init() { socketInitializeDefault(); }

void nspi::App::clean() { socketExit(); }

bool nspi::App::shouldClose() const { return this->quit || !appletMainLoop(); }

void nspi::App::mainLoop() {
  constexpr int targetFPS = 60;
  constexpr std::chrono::milliseconds targetFrameDuration(1000 / targetFPS);
  constexpr std::chrono::milliseconds inputCheckInterval(1);

  while (!this->shouldClose()) {
    auto frameStartTime = std::chrono::steady_clock::now();

    this->handleInput();
    this->draw();

    auto frameDuration = std::chrono::steady_clock::now() - frameStartTime;

    // Remaining time for current frame
    auto remainingTime = targetFrameDuration - frameDuration;

    while (remainingTime > inputCheckInterval) {
      this->handleInput();  // Check for input during frame capping
      std::this_thread::sleep_for(inputCheckInterval);
      remainingTime -= inputCheckInterval;
    }

    // Sleep for remaining time less than the input check interval
    if (remainingTime > std::chrono::milliseconds(0)) {
      std::this_thread::sleep_for(remainingTime);
    }
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
