#ifndef NSPI_MENU_H_
#define NSPI_MENU_H_

#include <cstdint>
#include <vector>

#include "nspi_pad.h"

namespace nspi {

struct Title {
  char id[17];
  char region[4];
  char name[50];
  uint16_t size;
};

class Menu {
 private:
  uint16_t focusIndex = 38;
  const uint8_t CONSOLE_WIDTH = 80;
  const uint8_t CONSOLE_HEIGHT = 44;
  const uint8_t HEADER_HEIGHT = 2;
  const uint8_t FOOTER_HEIGHT = 2;

  Pad& pad;
  std::vector<Title> dummyData;

  void printHeader() const;
  void printFooter() const;

  void focusPrevious();
  void focusNext();

 public:
  Menu(Pad&);
  ~Menu();

  Menu(const Menu&) = delete;
  Menu& operator=(const Menu&) = delete;

  void handleInput();
  void draw();
};

}  // namespace nspi

#endif  // NSPI_MENU_H_