#include "nspi_logger_menu.h"

// std
#include <iomanip>
#include <iostream>

#include "nspi_logger.h"

void nspi::LoggerMenu::printFooter() const {
  std::cout << "-------------------------------------------------------------------------------\n"
            << "[B] Back" << std::endl;
}

void nspi::LoggerMenu::printContent() const {
  std::stringstream output;

  int printedItems = 0;
  for (int i = focusOffset; i < dummyData.size(); i++) {
    if (printedItems >= VISIBLE_ITEMS) break;

    if (i == this->focusIndex) {
      output << "\033[1;41m";  // Highlight focused item
    } else if (this->marked.find(i) != this->marked.end()) {
      output << "\033[1;43m";  // Highlight marked item
    }

    output << dummyData[i] << "\033[0m" << std::endl;

    printedItems++;
  }

  // Padding for empty rows
  while (printedItems < VISIBLE_ITEMS) {
    output << std::endl;
    printedItems++;
  }

  std::cout << output.str();
}

nspi::LoggerMenu::LoggerMenu(MenuManager& menuManager, Pad& pad)
    : SelectableMenu(menuManager, pad) {
  this->dummyData = Logger::getLog();
}

void nspi::LoggerMenu::handleInput() { SelectableMenu::handleInput(); }
