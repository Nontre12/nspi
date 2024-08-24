#include "nspi_menu.h"

#include <iomanip>
#include <iostream>

#include "nspi_config.h"

void nspi::Menu::printHeader() const {
  std::stringstream app_info;
  app_info << APP_NAME << " Nintendo Switch v" << APP_VERSION << " by " << APP_AUTHOR_NAME;

  uint8_t remaining_width = CONSOLE_WIDTH - app_info.str().length();

  std::cout << app_info.str() << std::setw(remaining_width) << std::right << "SoC: 0'C\n";
  std::cout << "-------------------------------------------------------------------------------\n";
}

void nspi::Menu::printFooter() const {
  uint8_t printableFocusIndex = 0;
  if (this->dummyData.size() != 0) {
    printableFocusIndex = focusIndex + 1;
  }

  std::stringstream nav_info;
  nav_info << "(" << (int)printableFocusIndex << "/" << this->dummyData.size() << ")";

  uint8_t remaining_width = CONSOLE_WIDTH - nav_info.str().length();

  std::cout << "-------------------------------------------------------------------------------\n";
  std::cout << nav_info.str() << std::setw(remaining_width) << std::right
            << "[-] Load [+] Exit [X] De/Select [Y] Info [B] Back \e[9m[A] Install\e[0m\n";
}

void nspi::Menu::printContent() const {
  size_t printedItems = 0;
  for (size_t i = focusOffset; i < dummyData.size(); i++) {
    if (printedItems >= VISIBLE_ITEMS) break;

    if (i == this->focusIndex) {
      std::cout << "\033[1;41m";  // Highlight focused item
    } else if (this->marked.find(i) != this->marked.end()) {
      std::cout << "\033[1;43m";  // Highlight marked item
    }

    std::string name = dummyData[i].name;
    if (name.length() > 40) {
      name = name.substr(0, 37) + "...";
    }

    // clang-format off
    std::cout << std::setw(17) << std::left << dummyData[i].id
              << std::setw(3) << std::left << dummyData[i].region
              << std::setw(40) << std::left << name
              << std::setw(16) << std::right << dummyData[i].size << " MB"
              << "\033[0m" << std::endl;
    // clang-format on

    printedItems++;
  }

  // Padding for empty rows
  while (printedItems < VISIBLE_ITEMS) {
    std::cout << std::endl;
    printedItems++;
  }
}

nspi::Menu::Menu(Pad& pad) : focusIndex(0), focusOffset(0), pad(pad) {}

void nspi::Menu::handleInput() {
  u64 kDown = this->pad.getButtonsDown();
  HidAnalogStickState left_stick_state = this->pad.getStickPos(0);
  // HidAnalogStickState right_stick_state = this->pad.getStickPos(1);

  if (kDown & HidNpadButton_Up || left_stick_state.y > 30000) {
    this->focusPrevious();
  }

  if (kDown & HidNpadButton_Down || left_stick_state.y < -30000) {
    this->focusNext();
  }

  if (kDown & HidNpadButton_Left || left_stick_state.x < -30000) {
    this->focusPrevious(5);
  }

  if (kDown & HidNpadButton_Right || left_stick_state.x > 30000) {
    this->focusNext(5);
  }

  if (kDown & HidNpadButton_X) {
    if (this->marked.find(focusIndex) == this->marked.end()) {
      this->marked.insert(focusIndex);
    } else {
      this->marked.erase(focusIndex);
    }
  }

  // Adjust focusOffset if necessary
  if (focusIndex < focusOffset) {
    focusOffset = focusIndex;
  } else if (focusIndex >= focusOffset + VISIBLE_ITEMS) {
    focusOffset = focusIndex - VISIBLE_ITEMS + 1;
  }
}

void nspi::Menu::focusPrevious(uint16_t steps) {
  if (this->focusIndex < steps) {
    this->focusIndex = 0;
  }

  if (this->focusIndex != 0) {
    this->focusIndex -= steps;
  }
}

void nspi::Menu::focusNext(uint16_t steps) {
  if (this->dummyData.size() == 0) {
    this->focusIndex = 0;
    return;
  }

  if (this->focusIndex + steps > this->dummyData.size()) {
    this->focusIndex = this->dummyData.size() - 1;
  }

  if (this->focusIndex < this->dummyData.size() - 1) {
    this->focusIndex += steps;
  }
}

void nspi::Menu::draw() const {
  this->printHeader();
  this->printContent();
  this->printFooter();
}

void nspi::Menu::addEntries(const std::vector<nspi::Title>& titles) { this->dummyData = titles; }
