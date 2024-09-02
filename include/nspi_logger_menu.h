#ifndef NSPI_LOGGER_MENU_H_
#define NSPI_LOGGER_MENU_H_

// std
#include <cstdint>
#include <set>
#include <string>
#include <vector>

#include "nspi_app.h"
#include "nspi_menu.h"
#include "nspi_menu_manager.h"
#include "nspi_pad.h"
#include "nspi_selectable_menu.h"
#include "nspi_title.h"

namespace nspi {

class LoggerMenu : public SelectableMenu<std::string> {
 private:
  void printContent() const override;
  void printFooter() const override;

 public:
  explicit LoggerMenu(MenuManager&, Pad&);
  ~LoggerMenu() override = default;

  LoggerMenu(const LoggerMenu&) = delete;
  LoggerMenu& operator=(const LoggerMenu&) = delete;

  void handleInput() override;
};

}  // namespace nspi

#endif  // NSPI_LOGGER_MENU_H_