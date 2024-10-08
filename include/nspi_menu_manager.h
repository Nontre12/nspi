#ifndef NSPI_MENU_MANAGER_H_
#define NSPI_MENU_MANAGER_H_

// std
#include <stack>

#include "nspi_menu.h"
#include "nspi_pad.h"

namespace nspi {

class MenuManager {
 private:
  Pad &pad;
  std::stack<nspi::Menu *> menus;

  void init();
  void clean();

 public:
  explicit MenuManager(Pad &);
  ~MenuManager();

  MenuManager(const MenuManager &) = delete;
  MenuManager &operator=(const MenuManager &) = delete;

  void next(nspi::Menu *);
  void back();

  void handleInput();
  void draw() const;
};

}  // namespace nspi

#endif  // NSPI_MENU_MANAGER_H_