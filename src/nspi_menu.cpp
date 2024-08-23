#include "nspi_menu.h"

#include <iomanip>
#include <iostream>

#include "nspi_config.h"

void nspi::Menu::printHeader() const {
  std::cout << APP_NAME << " Nintendo Switch v" << APP_VERSION
            << "                                            SoC: 0'C\n";
  std::cout << "-------------------------------------------------------------------------------\n";
}

void nspi::Menu::printFooter() const {
  std::cout << "-------------------------------------------------------------------------------\n";
  std::cout << "(" << focusIndex + 1 << "/" << this->dummyData.size() << ")" << APP_AUTHOR_NAME
            << "            A - install  Y - menu             " << std::right << "Free: 5,00 MB\n";
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
    std::cout << std::setw(4) << std::left << dummyData[i].id << "  "
              << std::setw(4) << std::left << dummyData[i].region << "  "
              << std::setw(44) << std::left << name
              << std::setw(8) << std::right << dummyData[i].size << " MB"
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

nspi::Menu::Menu(Pad& pad) : focusIndex(0), focusOffset(0), pad(pad) {
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
      {"70010000000677", "EUR", "The Legend of Zelda: Link's Awakening", 5800},
      {"70010000000413", "EUR", "Super Mario Party", 2700},
      {"70010000000795", "EUR", "Donkey Kong Country: Tropical Freeze", 6500},
      {"70010000022343", "EUR", "Ring Fit Adventure", 2500},
      {"70010000008645", "EUR", "Metroid Dread", 4500},
      {"70010000027622", "EUR", "Pokemon Shield", 11000},
      {"70010000004206", "EUR", "Mario + Rabbids Kingdom Battle", 2900},
      {"70010000001609", "EUR", "Kirby Star Allies", 4200},
      {"70010000001592", "EUR", "ARMS", 2700},
      {"70010000009644", "EUR", "Octopath Traveler II", 4800},
      {"70010000000115", "EUR", "1-2-Switch", 1400},
      {"70010000016812", "EUR", "New Super Mario Bros. U Deluxe", 2600},
      {"70010000008747", "EUR", "Splatoon 3", 6100},
      {"70010000011797", "EUR", "Crash Bandicoot N. Sane Trilogy", 5600},
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
      {"70010000000677", "EUR", "The Legend of Zelda: Link's Awakening", 5800},
      {"70010000000413", "EUR", "Super Mario Party", 2700},
      {"70010000000795", "EUR", "Donkey Kong Country: Tropical Freeze", 6500},
      {"70010000022343", "EUR", "Ring Fit Adventure", 2500},
      {"70010000008645", "EUR", "Metroid Dread", 4500},
      {"70010000027622", "EUR", "Pokemon Shield", 11000},
      {"70010000004206", "EUR", "Mario + Rabbids Kingdom Battle", 2900},
      {"70010000001609", "EUR", "Kirby Star Allies", 4200},
      {"70010000001592", "EUR", "ARMS", 2700},
      {"70010000009644", "EUR", "Octopath Traveler II", 4800},
      {"70010000000115", "EUR", "1-2-Switch", 1400},
      {"70010000016812", "EUR", "New Super Mario Bros. U Deluxe", 2600},
      {"70010000008747", "EUR", "Splatoon 3", 6100},
      {"70010000011797", "EUR", "Crash Bandicoot N. Sane Trilogy", 5600},
  };
}

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
