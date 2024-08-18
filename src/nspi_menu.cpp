#include "nspi_menu.h"

#include <iomanip>
#include <iostream>

void nspi::Menu::printHeader() const {
  std::cout << "NSPi Nintendo Switch v0.0.1                                            SoC: 0'C\n";
  std::cout << "-------------------------------------------------------------------------------\n";
}

void nspi::Menu::printFooter() const {
  std::cout << "-------------------------------------------------------------------------------\n";
  std::cout << "Count: " << this->dummyData.size()
            << "\tNontre            A - install    Y - menu             Free: 5,00 MB\n";
}

nspi::Menu::Menu(Pad& pad) : pad(pad) {
  this->dummyData = {
      {"70010000000025", "EUR", "The Legend of Zelda: Breath of the Wild", 14300},
      {"70010000000031", "EUR", "Super Mario Odyssey", 5820},
      {"70010000027620", "EUR", "Animal Crossing: New Horizons", 6880},
      {"70010000000409", "EUR", "Splatoon 2", 6000},
      {"70010000000153", "EUR", "Mario Kart 8 Deluxe", 6910},
      {"70010000007354", "EUR", "Fire Emblem: Three Houses", 11800},
      {"70010000000443", "EUR", "Xenoblade Chronicles 2", 16000},
      {"70010000007388", "EUR", "Luigi's Mansion 3", 6820},
      {"70010000000539", "EUR", "Super Smash Bros. Ultimate", 16000},
      {"70010000020452", "EUR", "Hades", 1100},
      {"70010000002571", "EUR", "Octopath Traveler", 3100},
      {"70010000014949", "EUR", "The Witcher 3: Wild Hunt", 32000},
      {"70010000016534", "EUR", "Cuphead", 3900},
      {"70010000007418", "EUR", "Hollow Knight", 570},
      {"70010000027621", "EUR", "Pokemon Sword", 11000},
      {"70010000019618", "EUR", "Doom Eternal", 21000},
      {"70010000009762", "EUR", "Astral Chain", 10000},
      {"70010000001202", "EUR", "Stardew Valley", 800},
      {"70010000007010", "EUR", "Dark Souls: Remastered", 4000},
      {"70010000004438", "EUR", "The Elder Scrolls V: Skyrim", 14000},
      {"70010000007388", "EUR", "Bayonetta 2", 12800},
      {"70010000012216", "EUR", "Celeste", 1200},
      {"70010000016753", "EUR", "Dragon Quest XI S: Echoes of an Elusive Age", 14500},
      {"70010000034592", "EUR", "Monster Hunter Rise", 10700},
      {"70010000026388", "EUR", "Resident Evil 4", 12000},
  };
}

nspi::Menu::~Menu() {}

void nspi::Menu::handleInput() {
  u64 kDown = this->pad.getButtonsDown();
  if (kDown & HidNpadButton_A) {
    this->dummyData.push_back({"70010000009762", "EUR", "Astral Chain", 10000});
  }

  if (kDown & HidNpadButton_Up) {
    if (this->focusIndex != 0) {
      this->focusIndex--;
    }
  }

  if (kDown & HidNpadButton_Down) {
    if (this->focusIndex != this->CONSOLE_HEIGHT - 4 &&
        this->focusIndex < this->dummyData.size() - 1) {
      this->focusIndex++;
    }
  }
}

void nspi::Menu::draw() {
  this->printHeader();

  int index = 0;
  for (const Title& title : dummyData) {
    if (index == this->focusIndex) {
      std::cout << "\033[1;41m";
    }

    std::cout << title.id << "  ";
    std::cout << title.region << "  ";

    std::string name = title.name;
    if (name.length() > 40) {
      name = name.substr(0, 37) + "...";
    }

    std::cout << std::setw(44) << std::left << name;
    std::cout << std::setw(8) << std::right << title.size << " MB";

    if (index == this->focusIndex) {
      std::cout << "\033[0m";
    }

    std::cout << std::endl;

    index++;
  }

  // Padding for empty rows
  uint16_t i = this->dummyData.size() + HEADER_HEIGHT;
  while (i < CONSOLE_HEIGHT - FOOTER_HEIGHT) {
    std::cout << std::endl;
    i++;
  }

  this->printFooter();
}
