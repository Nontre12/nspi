#include "nspi_menu.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "nspi_config.h"

void nspi::Menu::printHeader() const {
  std::stringstream app_info;
  app_info << APP_NAME << " Nintendo Switch v" << APP_VERSION << " by " << APP_AUTHOR_NAME;

  uint8_t remaining_width = CONSOLE_WIDTH - app_info.str().length();

  std::cout << app_info.str() << std::setw(remaining_width) << std::right << "SoC: 0'C\n";
  std::cout << "-------------------------------------------------------------------------------\n";
}

void nspi::Menu::draw() const {
  this->printHeader();
  this->printContent();
  this->printFooter();
}