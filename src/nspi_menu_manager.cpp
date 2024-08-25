#include "nspi_menu_manager.h"

#include "nspi_title_selector_menu.h"

nspi::MenuManager::MenuManager(Pad &pad) : pad(pad) { this->init(); }

nspi::MenuManager::~MenuManager() { this->clean(); }

void nspi::MenuManager::init() { this->menus.push(new TitleSelectorMenu(*this, this->pad)); }

void nspi::MenuManager::clean() {
  while (!this->menus.empty()) {
    delete this->menus.top();
    this->menus.pop();
  }
}

void nspi::MenuManager::next(nspi::Menu *menu) { this->menus.push(menu); }

void nspi::MenuManager::back() {
  if (!this->menus.empty() && this->menus.size() != 1) {
    delete this->menus.top();
    this->menus.pop();
  }
}

void nspi::MenuManager::handleInput() {
  if (!this->menus.empty()) {
    this->menus.top()->handleInput();
  }
}

void nspi::MenuManager::draw() const {
  if (!this->menus.empty()) {
    this->menus.top()->draw();
  }
}