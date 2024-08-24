#include "nspi_title_menu.h"

// std
#include <iomanip>
#include <iostream>

#include "nspi_config.h"

void nspi::TitleMenu::printHeader() const {
  std::stringstream app_info;
  app_info << APP_NAME << " Nintendo Switch v" << APP_VERSION << " by " << APP_AUTHOR_NAME;

  uint8_t remaining_width = CONSOLE_WIDTH - app_info.str().length();

  std::cout << app_info.str() << std::setw(remaining_width) << std::right << "SoC: 0'C\n";
  std::cout << "-------------------------------------------------------------------------------\n";
}

void nspi::TitleMenu::printFooter() const {
  std::cout << "-------------------------------------------------------------------------------\n";
  std::cout << "[B] Back" << std::endl;
}

void nspi::TitleMenu::printContent() const {
  uint8_t labelWidth = 15;

  // clang-format off
  std::cout << std::left
            << std::setw(labelWidth) << "ID" << ": " << title.id << std::endl
            << std::setw(labelWidth) << "REGION" << ": " << title.region << std::endl
            << std::setw(labelWidth) << "PUBLISHER" << ": " << title.publisher << std::endl
            << std::setw(labelWidth) << "NAME" << ": " << title.name << std::endl
            << std::setw(labelWidth) << "SIZE" << ": " << title.size << " B" << std::endl
            << std::setw(labelWidth) << "VERSION" << ": " << title.version << std::endl
            << std::setw(labelWidth) << "RELEASE DATE" << ": " << title.releaseDate << std::endl;
  // clang-format on

  for (uint8_t i = 0; i < VISIBLE_ITEMS - 7; i++) {
    std::cout << std::endl;
  }
}

nspi::TitleMenu::TitleMenu(MenuManager& menuManager, Pad& pad, Title title)
    : menuManager(menuManager), pad(pad), title(title) {}

void nspi::TitleMenu::handleInput() {
  u64 kDown = this->pad.getButtonsDown();

  if (kDown & HidNpadButton_B) {
    this->menuManager.back();
  }
}

void nspi::TitleMenu::draw() const {
  this->printHeader();
  this->printContent();
  this->printFooter();
}
