#ifndef NSPI_TITLE_MENU_H_
#define NSPI_TITLE_MENU_H_

#include <cstdint>

#include "nspi_app.h"
#include "nspi_menu.h"
#include "nspi_menu_manager.h"
#include "nspi_pad.h"
#include "nspi_title.h"

namespace nspi {

class TitleMenu : public Menu {
 private:
  MenuManager& menuManager;
  Pad& pad;
  Title title;

  void printHeader() const;
  void printContent() const;
  void printFooter() const;

 public:
  explicit TitleMenu(MenuManager&, Pad&, Title);
  ~TitleMenu() = default;

  TitleMenu(const TitleMenu&) = delete;
  TitleMenu& operator=(const TitleMenu&) = delete;

  void handleInput();
  void draw() const;
};

}  // namespace nspi

#endif  // NSPI_TITLE_MENU_H_