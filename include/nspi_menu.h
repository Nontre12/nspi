#ifndef NSPI_MENU_H_
#define NSPI_MENU_H_

#include <cstdint>
#include <vector>
#include <set>

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
  static constexpr uint8_t CONSOLE_WIDTH = 80;
  static constexpr uint8_t CONSOLE_HEIGHT = 44;
  static constexpr uint8_t HEADER_HEIGHT = 2;
  static constexpr uint8_t FOOTER_HEIGHT = 2;

  uint16_t focusIndex;
  uint16_t focusOffset;

  Pad& pad;
  std::vector<Title> dummyData;

  std::set<uint16_t> marked;

  void printHeader() const;
  void printFooter() const;
  void focusPrevious();
  void focusNext();

 public:
  explicit Menu(Pad&);
  ~Menu() = default;

  Menu(const Menu&) = delete;
  Menu& operator=(const Menu&) = delete;

  void handleInput();
  void draw();
};

}  // namespace nspi

#endif  // NSPI_MENU_H_