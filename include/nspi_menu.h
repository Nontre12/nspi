#ifndef NSPI_MENU_H_
#define NSPI_MENU_H_

namespace nspi {

class Menu {
 public:
  virtual ~Menu() = default;
  virtual void handleInput() = 0;
  virtual void draw() const = 0;
};

}  // namespace nspi

#endif  // NSPI_MENU_H_