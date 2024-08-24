#ifndef NSPI_TITLE_SELECTOR_MENU_H_
#define NSPI_TITLE_SELECTOR_MENU_H_

#include <cstdint>
#include <set>
#include <string>
#include <vector>

#include "nspi_menu.h"
#include "nspi_pad.h"
#include "nspi_title.h"

namespace nspi {

class TitleSelectorMenu : public Menu {
 private:
  static constexpr uint8_t CONSOLE_WIDTH = 80;
  static constexpr uint8_t CONSOLE_HEIGHT = 44;
  static constexpr uint8_t HEADER_HEIGHT = 2;
  static constexpr uint8_t FOOTER_HEIGHT = 2;
  static constexpr uint8_t VISIBLE_ITEMS = CONSOLE_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT;

  uint16_t focusIndex;
  uint16_t focusOffset;
  std::set<uint16_t> marked;

  Pad& pad;
  std::vector<Title> dummyData;

  void printHeader() const;
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
  explicit TitleSelectorMenu(Pad&);
  ~TitleSelectorMenu() = default;

  TitleSelectorMenu(const TitleSelectorMenu&) = delete;
  TitleSelectorMenu& operator=(const TitleSelectorMenu&) = delete;

  void handleInput();
  void draw() const;
};

}  // namespace nspi

#endif  // NSPI_TITLE_SELECTOR_MENU_H_