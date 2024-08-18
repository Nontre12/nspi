#include "nspi_menu.h"

#include <iostream>

const uint8_t CONSOLE_WIDTH = 80;
const uint8_t CONSOLE_HEIGHT = 44;

const uint8_t limit = CONSOLE_HEIGHT - 4;

void nspi::Menu::printHeader() const {
  std::cout << "NSPi Nintendo Switch v0.0.1                                            SoC: 0'C\n";
  std::cout << "-------------------------------------------------------------------------------\n";
}

void nspi::Menu::printFooter() const {
  std::cout << "-------------------------------------------------------------------------------\n";
  std::cout << "Count: " << this->dummyData.size()
            << "\t\t\tA - install\tY - menu\t\t\tFree: 5,00 MB\n";
}

nspi::Menu::Menu() {}

nspi::Menu::~Menu() {}

void nspi::Menu::print() const {
  this->printHeader();

  for (size_t i = 0; i < this->dummyData.size() && i < limit; i++) {
    std::cout << this->dummyData[i].id << "\t" << this->dummyData[i].name << ""
              << this->dummyData[i].size + i << " MB\n";
  }

  for (int i = this->dummyData.size() + 2; i < 44 - 2; i++) {
    std::cout << "\033[1;41mbold red text\033[0m\n";
  }

  this->printFooter();
}

void nspi::Menu::__debug_push_back_list_element(Title title) { this->dummyData.push_back(title); }