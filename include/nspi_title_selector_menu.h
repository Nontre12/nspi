#ifndef NSPI_TITLE_SELECTOR_MENU_H_
#define NSPI_TITLE_SELECTOR_MENU_H_

#include <cstdint>
#include <set>
#include <string>
#include <vector>

#include "nspi_app.h"
#include "nspi_menu.h"
#include "nspi_menu_manager.h"
#include "nspi_pad.h"
#include "nspi_title.h"

namespace nspi {

class TitleSelectorMenu : public Menu {
 private:
  uint16_t focusIndex;
  uint16_t focusOffset;
  std::set<uint16_t> marked;

  MenuManager& menuManager;
  Pad& pad;
  std::vector<Title> dummyData;

  void printContent() const;
  void printFooter() const;

  /**
   * @param steps Amount of steps. Default 1
   */
  void focusPrevious(uint16_t steps = 1);
  /**
   * @param steps Amount of steps. Default 1
   */
  void focusNext(uint16_t steps = 1);

  std::string retrieveRawDataFromEndpoint(const std::string& endpoint) const;
  std::vector<nspi::Title> retrieveTitlesFromRawData(const std::string& rawData) const;
  std::vector<nspi::Title> fetchTitles(const std::string& endpoint) const;

 public:
  explicit TitleSelectorMenu(MenuManager&, Pad&);
  ~TitleSelectorMenu() = default;

  TitleSelectorMenu(const TitleSelectorMenu&) = delete;
  TitleSelectorMenu& operator=(const TitleSelectorMenu&) = delete;

  void handleInput();
};

}  // namespace nspi

#endif  // NSPI_TITLE_SELECTOR_MENU_H_