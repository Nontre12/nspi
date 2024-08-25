#include "nspi_title_menu.h"

// std
#include <iomanip>
#include <iostream>
#include <sstream>

void nspi::TitleMenu::printFooter() const {
  std::cout << "-------------------------------------------------------------------------------\n"
            << "[B] Back" << std::endl;
}

void nspi::TitleMenu::printContent() const {
  const uint8_t labelWidth = 15;

  std::stringstream output;

  // clang-format off
  output << std::left
         << std::setw(labelWidth) << "ID" << ": " << title.id << std::endl
         << std::setw(labelWidth) << "REGION" << ": " << title.region << std::endl
         << std::setw(labelWidth) << "PUBLISHER" << ": " << title.publisher << std::endl
         << std::setw(labelWidth) << "NAME" << ": " << title.name << std::endl
         << std::setw(labelWidth) << "SIZE" << ": " << title.size << " B" << std::endl
         << std::setw(labelWidth) << "VERSION" << ": " << title.version << std::endl
         << std::setw(labelWidth) << "RELEASE DATE" << ": " << title.releaseDate << std::endl;
  // clang-format on

  for (uint8_t i = 0; i < VISIBLE_ITEMS - 7; i++) {
    output << std::endl;
  }

  std::cout << output.str();
}

nspi::TitleMenu::TitleMenu(MenuManager& menuManager, Pad& pad, const Title& title)
    : menuManager(menuManager), pad(pad), title(title) {}

void nspi::TitleMenu::handleInput() {
  u64 kDown = this->pad.getButtonsDown();

  if (kDown & HidNpadButton_B) {
    this->menuManager.back();
  }
}
