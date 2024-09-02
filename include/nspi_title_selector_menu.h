#ifndef NSPI_TITLE_SELECTOR_MENU_H_
#define NSPI_TITLE_SELECTOR_MENU_H_

// std
#include <string>
#include <vector>

#include "nspi_menu_manager.h"
#include "nspi_selectable_menu.h"
#include "nspi_title.h"

namespace nspi {

class TitleSelectorMenu : public SelectableMenu<Title> {
 private:
  void printContent() const override;
  void printFooter() const override;

  std::string retrieveRawDataFromEndpoint(const std::string& endpoint) const;
  std::vector<nspi::Title> retrieveTitlesFromRawData(const std::string& rawData) const;
  std::vector<nspi::Title> fetchTitles(const std::string& endpoint) const;

 public:
  explicit TitleSelectorMenu(MenuManager&, Pad&);
  ~TitleSelectorMenu() override = default;

  TitleSelectorMenu(const TitleSelectorMenu&) = delete;
  TitleSelectorMenu& operator=(const TitleSelectorMenu&) = delete;

  void handleInput() override;
};

}  // namespace nspi

#endif  // NSPI_TITLE_SELECTOR_MENU_H_