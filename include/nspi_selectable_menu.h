#ifndef NSPI_SELECTABLE_MENU_H_
#define NSPI_SELECTABLE_MENU_H_

// std
#include <set>
#include <vector>

#include "nspi_menu.h"
#include "nspi_menu_manager.h"
#include "nspi_pad.h"

namespace nspi {

template <typename T>
class SelectableMenu : public Menu {
 protected:
  uint16_t focusIndex;
  uint16_t focusOffset;
  std::set<uint16_t> marked;

  MenuManager& menuManager;
  Pad& pad;
  std::vector<T> dummyData;

  virtual void printContent() const = 0;
  virtual void printFooter() const = 0;

  void focusPrevious(uint16_t steps = 1);
  void focusNext(uint16_t steps = 1);

 public:
  explicit SelectableMenu(MenuManager&, Pad&);
  ~SelectableMenu() override = default;

  SelectableMenu(const SelectableMenu&) = delete;
  SelectableMenu& operator=(const SelectableMenu&) = delete;

  void handleInput() override;
};

};  // namespace nspi

#endif  // NSPI_SELECTABLE_MENU_H_