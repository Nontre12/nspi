#ifndef NSPI_MENU_H_
#define NSPI_MENU_H_

#include <cstdint>
#include <vector>

namespace nspi {

struct Title {
  char id[17];
  char region[4];
  char name[50];
  uint16_t size;
};

class Menu {
 private:
  std::vector<Title> dummyData;

  void printHeader() const;
  void printFooter() const;

 public:
  Menu();
  ~Menu();

  Menu(const Menu&) = delete;
  Menu& operator=(const Menu&) = delete;

  void print() const;

  void __debug_push_back_list_element(Title title);
};

}  // namespace nspi

#endif  // NSPI_MENU_H_