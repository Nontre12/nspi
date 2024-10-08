#ifndef NSPI_MENU_H_
#define NSPI_MENU_H_

// std
#include <cstdint>

namespace nspi {

class Menu {
 protected:
  static constexpr uint8_t CONSOLE_WIDTH = 80;
  static constexpr uint8_t CONSOLE_HEIGHT = 44;
  static constexpr uint8_t HEADER_HEIGHT = 2;
  static constexpr uint8_t FOOTER_HEIGHT = 2;
  static constexpr uint8_t VISIBLE_ITEMS = CONSOLE_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT;

  virtual void printHeader() const;
  virtual void printContent() const = 0;
  virtual void printFooter() const = 0;

 public:
  virtual ~Menu() = default;
  virtual void handleInput() = 0;
  virtual void draw() const;
};

}  // namespace nspi

#endif  // NSPI_MENU_H_