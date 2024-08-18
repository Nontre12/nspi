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
  Pad& pad;
  std::vector<Title> dummyData;

  void printHeader() const;
  void printFooter() const;

 public:
  Menu(Pad&);
  ~Menu();

  Menu(const Menu&) = delete;
  Menu& operator=(const Menu&) = delete;

  void handleInput();
  void print() const;
};

}  // namespace nspi

#endif  // NSPI_MENU_H_