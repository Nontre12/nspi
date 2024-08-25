#include "nspi_menu.h"

// libnx
#include <switch.h>

// std
#include <iomanip>
#include <iostream>
#include <sstream>

#include "nspi_config.h"

void nspi::Menu::printHeader() const {
  std::stringstream output;

  output << APP_NAME << " Nintendo Switch v" << APP_VERSION << " by " << APP_AUTHOR_NAME;

  uint8_t remaining_width = CONSOLE_WIDTH - output.str().length();

  output << std::setw(remaining_width) << std::right << "SoC: 0'C\n";

  static AppletType at = appletGetAppletType();
  if (at != AppletType_Application && at != AppletType_SystemApplication) {
    output << "\033[1;41m------------------------- | APPLET MODE | WILL CRASH | "
              "------------------------\033[0m\n";
  } else {
    output << "-------------------------------------------------------------------------------\n";
  }

  std::cout << output.str();
}

void nspi::Menu::draw() const {
  this->printHeader();
  this->printContent();
  this->printFooter();
}