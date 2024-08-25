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
  const Title title;

  void printContent() const override;
  void printFooter() const override;

 public:
  explicit TitleMenu(MenuManager&, Pad&, const Title&);
  ~TitleMenu() override = default;

  TitleMenu(const TitleMenu&) = delete;
  TitleMenu& operator=(const TitleMenu&) = delete;

  void handleInput() override;
};

}  // namespace nspi

#endif  // NSPI_TITLE_MENU_H_