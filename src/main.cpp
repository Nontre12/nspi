#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "nspi_console.h"
#include "nspi_pad.h"

const uint8_t CONSOLE_WIDTH = 80;
const uint8_t CONSOLE_HEIGHT = 44;

namespace nspi {

struct Title {
  char id[17];
  char region[4];
  char name[50];
  uint16_t size;
};

}  // namespace nspi

std::vector<nspi::Title> dummyData = {};

uint8_t limit = CONSOLE_HEIGHT - 4;

void printMenu() {
  std::cout << "NSPi Nintendo Switch v0.0.1                                            SoC: 0'C\n";
  std::cout << "-------------------------------------------------------------------------------\n";
  for (size_t i = 0; i < dummyData.size() && i < limit; i++) {
    std::cout << dummyData[i].id << "\t" << dummyData[i].name << "" << dummyData[i].size + i
              << " MB\n";
  }

  for (int i = dummyData.size() + 2; i < 44 - 2; i++) {
    std::cout << "\033[1;41mbold red text\033[0m\n";
  }

  std::cout << "-------------------------------------------------------------------------------\n";
  std::cout << "Count: " << dummyData.size() << "\t\t\tA - install\tY - menu\t\t\tFree: 5,00 MB\n";
}

int main(int argc, char **argv) {
  nspi::Console console;
  nspi::Pad pad;

  while (appletMainLoop()) {
    pad.update();
    u64 kDown = pad.getButtonsDown();

    if (kDown & HidNpadButton_Plus) break;

    // code goes here
    if (kDown & HidNpadButton_A) {
      dummyData.push_back({"1000000000000000", "EUR", "Tiles of Zestyria", 12});
    }

    if (kDown & HidNpadButton_Up) {
      // focus up
    }

    if (kDown & HidNpadButton_Down) {
      // focus down
    }

    printMenu();

    console.update();
  }

  return 0;
}