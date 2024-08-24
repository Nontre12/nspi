#include "nspi_app.h"

// std
#include <iostream>
#include <sstream>

#include "nspi_title_selector_menu.h"

nspi::App::App() : quit(false) { this->init(); }

nspi::App::~App() { this->clean(); }

void nspi::App::init() {
  socketInitializeDefault();

  this->menu.push(new TitleSelectorMenu{pad});
}

void nspi::App::clean() {
  while (!this->menu.empty()) {
    delete this->menu.top();
    this->menu.pop();
  }

  socketExit();
}

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
  if (!this->menu.empty()) {
    this->menu.top()->handleInput();
  }
}

void nspi::App::draw() const {
  if (!this->menu.empty()) {
    this->menu.top()->draw();
  }

  this->console.update();
}

void nspi::App::run() { this->mainLoop(); }